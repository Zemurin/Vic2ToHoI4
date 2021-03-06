#include "IssuesFactory.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "IssueCategoryHelper.h"



Vic2::Issues::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		for (auto& name: IssueCategoryHelper{theStream}.takeIssues())
		{
			issues->issueNames.push_back(name);
		}
	});
}


std::unique_ptr<Vic2::Issues> Vic2::Issues::Factory::getIssues(const std::string& vic2Path)
{
	issues = std::make_unique<Issues>();
	parseFile(vic2Path + "/common/issues.txt");

	return std::move(issues);
}