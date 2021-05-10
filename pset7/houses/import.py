from cs50 import SQL
import csv
import sys

def main():
    if len(sys.argv) != 2:
        print("Incorrect Number of Arguments")
        return 1

    db = SQL("sqlite:///students.db")

    students_csv = csv.DictReader(open(sys.argv[1], 'r'))
    for row in students_csv:
        house = row["house"]
        birth = row["birth"]
        student_first_name = str(row["name"]).split()[0]
        if len(str(row["name"]).split()) == 3:
            student_middle_name = str(row["name"]).split()[1]
            student_last_name = str(row["name"]).split()[2]
        else:
            student_middle_name = None
            student_last_name = str(row["name"]).split()[1]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (:student_first_name, :student_middle_name, :student_last_name, :house, :birth);",
        student_first_name=student_first_name, student_middle_name=student_middle_name, student_last_name=student_last_name, house=house, birth=birth)

if __name__ == "__main__":
    main()