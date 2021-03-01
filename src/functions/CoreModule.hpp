// Auto-generated by compile-delayed-module from ../src/functions/CoreModule.xq
// DO NOT EDIT

// ../src/functions/CoreModule.xq
static const XMLCh core_file[] = { 46, 46, 47, 115, 114, 99, 47, 102, 117, 110, 99, 116, 105, 111, 110, 115, 47, 67, 111, 114, 101, 77, 111, 100, 117, 108, 101, 46, 120, 113, 0 };

// core
static const XMLCh core_prefix[] = { 99, 111, 114, 101, 0 };

// http://xqilla.sourceforge.net/core
static const XMLCh core_uri[] = { 104, 116, 116, 112, 58, 47, 47, 120, 113, 105, 108, 108, 97, 46, 115, 111, 117, 114, 99, 101, 102, 111, 114, 103, 101, 46, 110, 101, 116, 47, 99, 111, 114, 101, 0 };

static const DelayedModule::FuncDef core_functions[] = {
  {
    "to", 2, false, 20, 1,
    "declare function core:to($a as xs:integer?, $b as xs:integer?) as xs:decimal*\n"
    "{\n"
    "  if(empty($a) or empty($b)) then ()\n"
    "  else core:to_helper($a treat as xs:decimal, $b treat as xs:decimal)\n"
    "}\n"
  },
  {
    "to_helper", 2, false, 26, 1,
    "declare function core:to_helper($a as xs:decimal, $b as xs:decimal) as xs:decimal*\n"
    "{\n"
    "  if($a gt $b) then () else ($a, core:to_helper($a + 1, $b))\n"
    "}\n"
  },
  { 0, 0, 0, 0, 0 }
};

static const DelayedModule core_module = { core_file, core_prefix, core_uri, core_functions };
