#include <iostream>

#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include <numeric>


enum Grade
{
	F = 1,
	D,
	C,
	B,
	A
};

struct Student
{
	std::string FIO;
	std::string Group;
	std::map<std::string, Grade> Grades;
};



std::pair<Student, size_t> max_m_grades;



std::vector<Student> LoadStudents()
{
	return{
		{
			"Anna", "G7",
			{
				{ "math", Grade::B },
				{ "cs", Grade::A },
				{ "english", Grade::A },
				{ "dutch", Grade::B },
			}
		},
		{
			"Petr", "G7",
			{
				{ "math", Grade::A },
				{ "cs", Grade::B },
				{ "dutch", Grade::C },
			}
		},
		{
			"Vova", "G1",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
			}
		},
		{
			"Vasya", "G3",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
				{ "cs", Grade::B },
				{ "dutch", Grade::C },
			}
		},
		{
			"Anton", "G4",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
				{ "dutch", Grade::C },
				{ "cs", Grade::C },
			}
		},
		{
			"Masha", "G2",
			{
				{ "math", Grade::A },
			}
		},
		{
			"Sasha", "G6",
			{
				{ "english", Grade::F },
				{ "russian", Grade::F },
				{ "dutch", Grade::F },
			}
		},
		{
			"Jeka", "G2",
			{
				{ "english", Grade::A },
			}
		},
		{
			"Sveta", "G3",
			{
			}
		}
	};
}


struct MathGradeEqual
{
	size_t grade;

	bool operator()(const Student & student) const
	{
		if (student.Grades.find("math") != student.Grades.end()) 
			return student.Grades.find("math")->second == grade;
		return false;
	}
};


struct StudentsOfGroup
{

	std::string Group;
	std::vector<Student> Students;

	StudentsOfGroup(const std::string & group) 
		: Group(group)
	{
		std::vector<Student> buf = LoadStudents();
		for (auto & i : buf)
			if (i.Group == Group)
				Students.push_back(i);
	}

};




int main()
{
	std::vector<Student> students = LoadStudents();


	for (size_t i = 5; i > 0; --i) {
		auto it = std::find_if(students.begin(), students.end(), MathGradeEqual { i });
		if (it != students.end()) {
			std::cout << it->FIO << std::endl;
			break;
		}
	}

	max_m_grades.first = *students.begin();
	max_m_grades.second = 0;


	std::for_each(students.begin(), students.end(),
		[](const Student & student)
	{
		size_t result(0);
		size_t j(0);
		for (auto & i : student.Grades) {
			result += i.second;
			++j;
		}
		if (j != 0 && (result / j) > max_m_grades.second) {
			max_m_grades.first = student;
			max_m_grades.second = result / j;
		}
	}	
	);
	std::cout << max_m_grades.first.FIO << " " << max_m_grades.second << std::endl;

	max_m_grades.first = *students.begin();
	max_m_grades.second = 0;

	std::for_each(students.begin(), students.end(),
		[](const Student & student)
	{
		if (student.Grades.size() > max_m_grades.second) {
			max_m_grades.first = student;
			max_m_grades.second = student.Grades.size();
		}
	}
	);
	std::cout << max_m_grades.first.FIO << " " << max_m_grades.second << std::endl;

	StudentsOfGroup G7 = { "G7" };

	for (auto & i : G7.Students)
		std::cout << i.FIO << std::endl;


	std::for_each(students.begin(), students.end(),
		[](const Student & student)
	{
		if (student.Grades.find("math") != student.Grades.end() &&
			student.Grades.find("cs") != student.Grades.end() &&
			student.Grades.find("math")->second == 4 &&
			student.Grades.find("cs")->second == 5) 
		{
			std::cout << student.FIO << " has 4 in math and 5 in cs" << std::endl;
		}
	}
	);


	std::for_each(students.begin(), students.end(),
		[](Student & student)
	{
		size_t result(0);
		size_t j(0);
		for (auto & i : student.Grades) {
			result += i.second;
			++j;
		}
		if (j != 0)
			result /= j;
			
		student.Grades.insert(std::make_pair(std::string("Russian literature"),
			Grade(static_cast<size_t>(ceil(result)))));
	}
	);

	for (auto & i : students)
		std::cout << i.FIO << " has " << i.Grades.find("Russian literature")->second 
		<< " in Russian literature" << std::endl;
	
	std::for_each(students.begin(), students.end(),
		[](Student & student)
	{
		if (student.Grades.find("dutch") != student.Grades.end())
			std::cout << student.FIO << " has " << student.Grades.find("dutch")->second
			<< " in dutch" << std::endl;
		else
			std::cout << student.FIO << " hasn't dutch" << std::endl;

	}
	);

	system("pause");

}
