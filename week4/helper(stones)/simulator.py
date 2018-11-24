"""Python script for testing your solution on your computer
To avoid encoding issues, all instructions are written in English.
You are always free to ask about the testing tool on the Piazza board.

WARNING: This script is only a convenient way to test your solution,
but obviously IT IS NOT SAME WITH THE REAL JUDGING SYSTEM.
The judging system might behave differently.
"""

from __future__ import print_function
import sys
import subprocess
import argparse

parser = argparse.ArgumentParser("Local testing script for problem 'minmax'.")

parser.add_argument('--input', metavar='INPUTFILENAME', type=argparse.FileType('r'), help='Input file written as the problem statement. If not specified, example input is used.')
parser.add_argument('-l', '--log', help='If specified, show all interaction log', action='store_true')
parser.add_argument('--limit', metavar='LIMIT', type=int, help='Maximum number of weighing requests. Defaults to 900.', default=900)
parser.add_argument('command', nargs=argparse.REMAINDER, help='Command to run your C/C++/Java program. You should NOT wrap it with quotation marks.\n')
args = parser.parse_args()

PRINT_INTERACTION_HISTORY = args.log
MAX_WEIGHINGS = args.limit

if args.input is None:
  TESTDATA = [[5, 1, 3, 4, 2], [1, 1, 2, 3, 4, 4], [7, 3, 1, 4, 2, 6, 5], [10]]
else:
  try:
    with args.input as f:
      TESTDATA = []
      tokens = f.read().split()
      token_idx = 0
      def next():
        global token_idx
        if token_idx == len(tokens):
          raise ValueError("Number of tokens doesn't match.")
        token_idx += 1
        return int(tokens[token_idx-1])
      num_tests = next()
      if num_tests < 1:
        raise ValueError("The number of tests ({}) is not positive.".format(num_tests))
      for _ in range(num_tests):
        n = next()
        if n < 1 or n > 600:
          raise ValueError("n is out of range [1, 600].")
        a = []
        for i in range(n):
          a.append(next())
        TESTDATA.append(a)
  except ValueError as e:
    print("Input file format is wrong, please check again: {}".format(str(e)))
    sys.exit(-1)
  except Exception as e:
    print("Error while parsing input file {}: {}".format(args.input, str(e)))
    sys.exit(-1)


"""Helper functions"""
def JudgePrint(p, s):
  # Print the judge output to your code's input stream. Log this interaction
  # to console (stdout) if PRINT_INTERACTION_HISTORY is True.
  print(s, file=p.stdin)
  p.stdin.flush()
  if PRINT_INTERACTION_HISTORY:
    print("Judge prints:", s)


def PrintSubprocessResults(p):
  # Print the return code and stderr output for your code.
  print("Your code finishes with exit status {}.".format(p.returncode))
  code_stderr_output = p.stderr.read()
  if code_stderr_output:
    print("The stderr output of your code is:")
    sys.stdout.write(code_stderr_output)
  else:
    print("Your code doesn't have stderr output.")


def WaitForSubprocess(p):
  # Wait for your code to finish and print the stderr output of your code for
  # debugging purposes.
  if p.poll() is None:
    print("Waiting for your code to finish...")
    p.wait()
  PrintSubprocessResults(p)


def CheckSubprocessExit(p, case_id):
  # Exit if your code finishes in the middle of a test case.
  if p.poll() is not None:
    print("Your code exited early, in the middle of Case #{}.".format(case_id))
    PrintSubprocessResults(p)
    sys.exit(-1)


def WrongAnswerExit(p, case_id, error_msg):
  print("Case #{} failed: {}".format(case_id, error_msg))
  try:
    JudgePrint(p, "-202")
  except IOError:
    print("Failed to print -202 because your code finished already.")
  WaitForSubprocess(p)
  sys.exit(-1)


def ReadIntList(n, line):
  tok = line.split()
  try:
    l = int(tok[0])
    if len(tok) != l+1:
      return "Wrong number of tokens: \"{}\": expected {} integers, {} tokens given".format(line, l, len(tok)-1)
    
    a = [int(x) for x in tok[1:]]
    for x in a:
      if x < 1 or x > n:
        return "Integer {} is not in range [{}-{}]".format(x, 1, n)
    return a
  except ValueError:
    return "A token in {} is not an integer.".format(line)


"""Main function begins"""
# Retrieve the command to run your code from the arguments.
# If you cannot pass arguments to Python when running this testing tool, please
# replace sys.argv[1:] with the command list to run your code.
# e.g. C/C++ users: cmd = ["./my_binary"]
#      Java users: cmd = ["java", "my_main_class_name"]
cmd = args.command
if len(cmd) == 0:
  print("You should provide a command to execute your code.")
  exit(0)

# Run your code in a separate process. You can debug your code by printing to
# stderr inside your code, or adding print statements in this testing tool.
# Note that your stderr output will be printed by this testing tool only after
# your code finishes, e.g. if your code hangs, you wouldn't get your stderr
# output.
try:
  p = subprocess.Popen(
      cmd,
      stdin=subprocess.PIPE,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE,
      bufsize=1,
      universal_newlines=True)
except Exception as e:
  print("Failed to start running your code. Error:")
  print(e)
  sys.exit(-1)

JudgePrint(p, len(TESTDATA))
for test_case_id in range(1, 1+len(TESTDATA)):
  arr = TESTDATA[test_case_id - 1]
  if PRINT_INTERACTION_HISTORY:
    print("Test Case #{}:".format(test_case_id))
  JudgePrint(p, "%d" % len(arr))
  test_case_passed = False
  for num_queries in range(MAX_WEIGHINGS+1):
    user_input = None
    try:
      user_input = p.stdout.readline()
      tokens = user_input.split()
      if len(tokens) == 0:
        raise Exception()
    except:
      CheckSubprocessExit(p, test_case_id)
      exit_msg = ""
      if user_input.strip() == "":
        exit_msg = (
            "Read an empty string, instead of reading any tokens."
            "This might happen because your code exited early, or printed an "
            "extra newline character.")
      elif user_input is None:
        exit_msg = (
            "Unable to read anything from your program. This might happen because your "
            "code exited early, printed an extra new line character, or did "
            "not print the output correctly.")
      WrongAnswerExit(p, test_case_id, exit_msg)
    
    if PRINT_INTERACTION_HISTORY:
      print("Judge reads:", user_input.rstrip())

    if tokens[0] == "?":
      try:
        i, j = map(int, tokens[1:])
      except:
        WrongAnswerExit(p, test_case_id, 
          "Failed to read the weighing request. Expected '?' and two integers ending with one newline character."
          "Read \"{}\" (quotes added to isolate output of your program) instead".format(user_input))
        
      if (i < 1) or (i > len(arr)) or (j < 1) or (j > len(arr)):
        WrongAnswerExit(p, test_case_id, "Your input is out of range [1, N = {}].".format(len(arr)))

      if i == j:
        WrongAnswerExit(p, test_case_id, "You are weighing the same stone #{}.".format(i))
      
      i -= 1
      j -= 1
      comp_res = '='
      if arr[i] > arr[j]:
        comp_res = '>'
      elif arr[i] < arr[j]:
        comp_res = '<'
      
      JudgePrint(p, comp_res)
    elif tokens[0] == "!":
      if len(tokens) != 1:
        WrongAnswerExit(p, test_case_id, "You should print '!' in a separate line.") 
      try:
        line = p.stdout.readline()
        min_pos_user = ReadIntList(len(arr), line)
        line = p.stdout.readline()
        max_pos_user = ReadIntList(len(arr), line)
      except Exception as e:
        CheckSubprocessExit(p, test_case_id)
        WrongAnswerExit(p, test_case_id, e)
      
      min_val = min(arr)
      max_val = max(arr)
      min_pos = []
      max_pos = []
      for i in range(len(arr)):
        if arr[i] == min_val:
          min_pos.append(i + 1)
        if arr[i] == max_val:
          max_pos.append(i + 1)

      min_pos_user.sort()
      max_pos_user.sort()

      if min_pos_user == min_pos and max_pos_user == max_pos:
        test_case_passed = True
        break
      
      WrongAnswerExit(p, test_case_id,
        "Failed to report all lightest and heaviest stones correctly.\n"
        "Expected: lightest = {}, heaviest = {}\n"
        "Read: lightest = {}, heaviest = {}".format(min_pos, max_pos, min_pos_user, max_pos_user))
    else:
      WrongAnswerExit(p, test_case_id, "Each line should start with ? or !")
  if not test_case_passed:
    WrongAnswerExit(p, test_case_id,
      "Failed to report all lightest and heaviest stones in {} weighings.".format(MAX_WEIGHINGS))

extra_output = p.stdout.readline()
WaitForSubprocess(p)
if extra_output == "":
  print("Congratulations! All test cases passed :)")
else:
  print("Wrong Answer because of extra output:")
  sys.stdout.write(extra_output)
  sys.exit(-1)

