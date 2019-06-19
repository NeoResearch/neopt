#include "ImportBlocksSettings.h"

using namespace std;
using namespace neopt;

ImportBlocksSettings* ImportBlocksSettings::_default = nullptr;

ImportBlocksSettings::ImportBlocksSettings(const ConfigurationSection& section)
{
   std::function<uint(string)> sel = parse_uint;
   this->MaxOnImportHeight = GetValueOrDefault(section.GetSection("MaxOnImportHeight"), 0u, sel);
}
