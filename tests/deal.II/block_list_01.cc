//----------------------------------------------------------------------
//    $Id$
//    Version: $Name$ 
//
//    Copyright (C) 2009, 2010, 2011 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------------------------------------------------

#include "block_list.h"

template <int dim>
void
test_block_list(const Triangulation<dim>& tr, const FiniteElement<dim>& fe)
{
  deallog << fe.get_name() << std::endl;
  
  MGDoFHandler<dim> dof;
  dof.initialize(tr, fe);
  
  
  const unsigned int level = tr.n_levels()-1;
  
  SparsityPattern bl(tr.n_cells(level), dof.n_dofs(level), fe.dofs_per_cell);
  DoFTools::make_cell_patches(bl, dof, level);
  bl.compress();
  
  for (unsigned int i=0;i<bl.n_rows();++i)
    {
      deallog << "Block " << std::setw(3) << i;
      std::vector<unsigned int> entries;
      for (SparsityPattern::row_iterator b = bl.row_begin(i);b != bl.row_end(i);++b)
	entries.push_back(*b);

      std::sort(entries.begin(), entries.end());

      for (unsigned int i=0;i<entries.size();++i)
	deallog << ' ' << std::setw(4) << entries[i];
      deallog << std::endl;
    }
}


int main()
{
  initlog(__FILE__);
  deallog.push("2D");
  test_global_refinement<2>(&test_block_list<2>);
  deallog.pop();
  deallog.push("3D");
  test_global_refinement<3>(&test_block_list<3>);
  deallog.pop();
}
