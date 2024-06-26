#include "src/V2World/Wars/WarGoalFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::WarGoalFactory::WarGoalFactory()
{
	registerKeyword("casus_belli", [this](std::istream& theStream) {
		casusBelli = commonItems::getString(theStream);
	});
	registerKeyword("state_province_id", [this](std::istream& theStream) {
		province = commonItems::getInt(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


Vic2::WarGoal Vic2::WarGoalFactory::getWarGoal(std::istream& theStream)
{
	casusBelli.clear();
	province.reset();
	parseStream(theStream);
	return WarGoal{.casusBelli = casusBelli, .province = province};
}