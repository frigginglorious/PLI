#include "modules/gambit/driver.hpp"

Gambit::Driver::~Driver()
{
   std::cout << "Deleting Gambit::Driver" << std::endl;
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
   delete(tree);
   tree = nullptr;
}

int
Gambit::Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ) exit( EXIT_FAILURE );

   delete(scanner);
   try
   {
      scanner = new Gambit::Scanner( &in_file );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   delete(parser);
   try
   {
      parser = new Gambit::Parser( (*scanner), (*this) );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   return parser->parse();
}

AST::Tree*
Gambit::Driver::getTree()
{
  return this->tree;
}

void
Gambit::Driver::setTree(AST::Tree* tree)
{
  this->tree = tree;
}