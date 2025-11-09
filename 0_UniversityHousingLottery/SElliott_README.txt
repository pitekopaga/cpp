Scott Elliott
University Housing Lottery Program README

Overview

The University Housing Lottery Program is a C++ application that calculates housing priority points for students based on specific criteria. Higher points increase a student’s chances of securing their preferred housing option. The program collects student information (name, class year, age, academic probation status, academic suspension status, disciplinary probation status, and student teacher status) and assigns points according to a defined scoring system. It allows multiple students to be entered in a single run and displays a ranked list of students sorted by total points in descending order.

Scoring System

The program assigns points based on the following criteria:

Class Year:

Freshman: +1 point
Sophomore: +2 points
Junior: +3 points
Senior: +4 points
Invalid input (e.g., "Graduate"): 0 points

Age:
Age 23–49: +1 point
Age 50–150 (with reasonable accommodations): +2 points
Age 50–150 (without accommodations): +1 point
Age 0–22: 0 points
Invalid age (e.g., non-numeric, negative, >150): 0 points

Academic Probation:

On probation: -1 point
Not on probation: 0 points
Academic Suspension:
On suspension: -2 points
Not on suspension: 0 points

Disciplinary Probation:
On disciplinary probation: -3 points
Not on disciplinary probation: 0 points

Student Teacher Status:
Student teacher: +2 points
Not a student teacher: 0 points

The total points determine a student’s priority, with higher points indicating a higher rank in the housing lottery.

Sample Output

Below is a sample output aggregating three test cases in a single run, demonstrating the program’s ability to handle multiple students and compare their points. The test cases are:

John Doe: 25-year-old senior on academic probation
Jane Smith: 22-year-old junior who is a student teacher
Alex Johnson: 20-year-old sophomore on disciplinary probation

Housing Lottery Results:
**************************
Rank    Name            Points
----    ----            ------
1       Jane Smith      5
2       John Doe        4
3       Alex Johnson    -1

********************************************************************
Thank you for using the University Housing Lottery Program. Goodbye!

John Doe: Senior (+4) + Age 25 (+1) + Academic Probation (-1) + Student Teacher (0) = 4 points
Jane Smith: Junior (+3) + Age 22 (0) + Student Teacher (+2) = 5 points
Alex Johnson: Sophomore (+2) + Age 20 (0) + Disciplinary Probation (-3) + Student Teacher (0) = -1 points

The housing lottery scoring system prioritizes students based on seniority, maturity, contributions to the university, and disciplinary status, but its fairness is mixed due to the weighting of criteria and potential biases.

Students likely to benefit most are Seniors who receive the highest class year points (+4), giving them a significant advantage, as seen with John Doe (4 points). This prioritizes students closer to graduation, which may be fair given their longer tenure and potential housing needs.

Older Students (Age 23+) and students aged 23–49 earn +1 point (e.g., John Doe), and those 50+ can earn up to +2 points with accommodations, benefiting non-traditional students who may require stable housing.

Student Teachers earn 2 points, as seen with Jane Smith (5 points), rewards contributions to the university’s educational mission, giving them a competitive edge, especially for juniors or seniors.

Students with Clean Records, including those not on academic or disciplinary probation avoid deductions, maximizing their points, as seen with Jane Smith’s high ranking.

Students Likely to Be Left Out are Freshmen and Sophomores: Freshmen (+1) and sophomores (+2) who receive fewer points than juniors (+3) or seniors (+4), as seen with Alex Johnson (-1 point), potentially disadvantaging newer students with equal housing needs.

Younger Students under 23 receive no age points (e.g., Jane Smith, Alex Johnson), which may unfairly penalize traditional-aged undergraduates, who are often the majority.

Students on Disciplinary Probation get a 3 point penalty for disciplinary probation, as seen with Alex Johnson. It is the heaviest deduction and a significantly lowering priority. This could disproportionately harm students with minor infractions compared to academic probation (-1) or suspension (-2).

Non-Student Teachers: Students who are not student teachers miss out on 2 points (e.g., John Doe, Alex Johnson), which may disadvantage those with other contributions (e.g., research assistants) not recognized by the system.

The program is partially fair because it rewards seniority (class year), contributions (student teacher status), and accessibility (age-based accommodations), aligning with common university priorities. The +2 points for student teachers fairly recognizes their educational role, as seen with Jane Smith’s top ranking. However, it may be unfair to younger students and those on disciplinary probation. The -3 point penalty for disciplinary probation can result in negative points (e.g., Alex Johnson’s -1), severely limiting housing options, which may be overly punitive for minor infractions. Younger students and freshmen/sophomores are consistently outranked, potentially overlooking their needs (e.g., financial hardship). 

To enhance fairness, consider reducing the disciplinary probation penalty (e.g., -2) to be less severe, or adding points for other contributions (e.g., leadership, volunteering) or needs (e.g., financial aid status).

The program includes comprehensive input validation to handle invalid user input gracefully without crashing. For age input, it uses robust exception handling to catch non-numeric values and displays clear error messages while awarding zero points for invalid entries. All boolean inputs (probation, suspension, disciplinary status, and student teacher status) accept multiple formats including "1"/"0" and "Y"/"N" with case-insensitive matching, continuously prompting until valid input is received. Class year validation supports case-insensitive matching for recognized options and awards zero points for unrecognized inputs. Name validation prevents empty entries, and all continue prompts validate yes/no responses. The program uses dedicated helper functions with try-catch blocks and input sanitization to ensure stability across all user interactions.

AI Tool Usage

Questions about the University Housing Lottery Program and introductory C++ tutorials were asked, particularly regarding C++ syntax with data validation. Some of the code in the data validation helper functions were influenced iteratively based on feedback to fix bugs. No external AI tools were used to generate or modify the code. Some of the README content was generated by Grok, created by xAI, in response to the user’s prompt:

Prompt: “which students should be given higher priority at housing in college”

AI Contribution:

Code: The code itself was not generated by Grok or any other AI tool in this response. It was based on the user’s provided code, with modifications made in previous interactions to fix bugs.

Citation: Grok (xAI). (2025). Used to provide technical assistance in debugging code and gaining insight into which students should be prioritized housing in college. No external AI tools were used for code generation.