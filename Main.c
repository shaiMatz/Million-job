#include "candidate.h"
#include "employer.h"
#include "menu.h"




int main()
{
	//menu();
	//employer newEmployer = employer_Registration();
	//newEmployer = resetPassword2(newEmployer);
	candidate newCandidate = Candidate_Registration();
	newCandidate = resetPassword(newCandidate);
	//candidate newC = loginC("shyshir@gmail.com");
	//editProfile(newC, "Candidate_DATA.csv", 3);
	//char candidateName[50] = "shai";
	//CVFile(candidateName);

	return 0;

}






