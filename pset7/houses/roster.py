from cs50 import SQL
import sys

def main():
    if len(sys.argv) != 2:
        print("Incorrect Number of Arguments")
        return 1

    db = SQL("sqlite:///students.db")

    house_name = str(sys.argv[1])
    students_info = db.execute("SELECT * FROM students WHERE students.house = :house ORDER BY last, first;", house=house_name)

    for row in students_info:
        if row["middle"]:
            print("%s %s %s, born %s"% (row["first"], row["middle"], row["last"], row["birth"]))
        else:
            print("%s %s, born %s"% (row["first"], row["last"], row["birth"]))

if __name__ == "__main__":
    main()
