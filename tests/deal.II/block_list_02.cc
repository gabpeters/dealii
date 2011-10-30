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

  {
    deallog.push("tttt");
    SparsityPattern bl;
    DoFTools::make_vertex_patches(bl, dof, level, true, true, true, true);
    bl.compress();
    print_patches(bl);
    deallog.pop();
    deallog << std::endl;
  }
  {
    deallog.push("ttff");
    SparsityPattern bl;
    DoFTools::make_vertex_patches(bl, dof, level, true, true, false);
    bl.compress();
    print_patches(bl);
    deallog.pop(); 
    deallog << std::endl;
  }
  {
    deallog.push("tfff");
    SparsityPattern bl;
    DoFTools::make_vertex_patches(bl, dof, level, true, false, false);
    bl.compress();
    print_patches(bl);
    deallog.pop();
    deallog << std::endl;
  }
  {
    deallog.push("fttt");
    SparsityPattern bl;
    DoFTools::make_vertex_patches(bl, dof, level, false, true, true, true);
    bl.compress();
    print_patches(bl);
    deallog.pop();
    deallog << std::endl;
  }
  {
    deallog.push("ffff");
    SparsityPattern bl;
    DoFTools::make_vertex_patches(bl, dof, level, false, false, false);
    bl.compress();
    print_patches(bl);
    deallog.pop();
    deallog << std::endl;
  }
}


int main()
{
  initlog(__FILE__, true);
  deallog.push("2D");
  test_global_refinement<2>(&test_block_list<2>);
  deallog.pop();
  deallog.push("3D");
  test_global_refinement<3>(&test_block_list<3>);
  deallog.pop();
}
