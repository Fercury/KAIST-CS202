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

parser = argparse.ArgumentParser("Local testing script for problem 'chaltteok'.")

parser.add_argument('--input', metavar='INPUTFILENAME', type=argparse.FileType('r'), help='Input file written as the problem statement. If not specified, example input is used.')
parser.add_argument('-l', '--log', help='If specified, show all interaction log', action='store_true')
parser.add_argument('--limit', metavar='LIMIT', type=int, help='Maximum number of turns. Defaults to 20000.', default=20000)
parser.add_argument('command', nargs=argparse.REMAINDER, help='Command to run your C/C++/Java program. You should NOT wrap it with quotation marks.\n')
args = parser.parse_args()

PRINT_INTERACTION_HISTORY = args.log
MAX_TURNS = args.limit

if args.input is None:
  TESTDATA = [4, 2, 3, 1, 5]
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
      n = next()
      if n < 1:
        raise ValueError("N ({}) is not positive.".format(n))
      chk = [0 for _ in range(n)]
      for _ in range(n):
        val = next()
        if val < 1 or val > n:
          raise ValueError("value is out of range [1, N].")
        val -= 1
        if chk[val] > 0:
          raise ValueError("duplicated value exists.")
          chk[val] = 1
        TESTDATA.append(val+1)
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

for test_case_id in range(1, 2):
  if PRINT_INTERACTION_HISTORY:
    print("Test Case:")
  n = len(TESTDATA)
  JudgePrint(p, "%d" % n)
  test_case_passed = False
  for num_queries in range(MAX_TURNS+1):
    user_input = None
    try:
      user_input = p.stdout.readline()
      tokens = user_input.split()
      if len(tokens) == 0:
        raise Exception()
    except:
      CheckSubprocessExit(p, 1)
      exit_msg = ""
      if user_input is None:
        exit_msg = (
            "Unable to read anything from your program. This might happen because your "
            "code exited early, printed an extra new line character, or did "
            "not print the output correctly.")
      elif user_input.strip() == "":
        exit_msg = (
            "Read an empty string, instead of reading any tokens."
            "This might happen because your code exited early, or printed an "
            "extra newline character.")
      WrongAnswerExit(p, test_case_id, exit_msg)
    
    if PRINT_INTERACTION_HISTORY:
      print("Judge reads:", user_input.rstrip())

    if tokens[0] == "?":
      try:
        sel = list(map(int, tokens[1:]))
      except:
        WrongAnswerExit(p, test_case_id, 
          "Failed to read request. Expected '?' and integers ending with one newline character."
          "Read \"{}\" (quotes added to isolate output of your program) instead".format(user_input))
      
      if len(sel) != sel[0] + 1:
        WrongAnswerExit(p, test_case_id,
          "Invalid request. number of tteok(s) expected: %d, but you sent %d tteok(s)." % (sel[0], len(sel) - 1))
      
      chk = [0 for _ in range(n+1)]
      for val in sel[1:]:
        if val < 1 or val > n:
          WrongAnswerExit(p, test_case_id, "Your input is out of range [1, N = {}].".format(n))
        if chk[val] > 0:
          WrongAnswerExit(p, test_case_id, "Duplicated value in query: {}.".format(val))
        chk[val] = 1
      seq = [chk[val] for val in TESTDATA]
      return_value = seq[0]
      for i in range(1, n):
        if seq[i] > 0 and seq[i-1] == 0:
          return_value += 1
      JudgePrint(p, return_value)
    elif tokens[0] == "!":
      try:
        user_ans = list(map(int, tokens[1:]))
        if len(user_ans) != n:
          raise Exception()
        chk = [0 for _ in range(n+1)]
        for val in user_ans:
          if val < 1 or val > n or chk[val] > 0:
            raise Exception()
          chk[val] = 1
      except:
        WrongAnswerExit(p, test_case_id, 
          "Failed to read request. Expected '!' and N distinct integers (permutation) ending with one newline character."
          "Read \"{}\" (quotes added to isolate output of your program) instead".format(user_input))
      
      real_ans1 = TESTDATA[:]
      real_ans2 = TESTDATA[:]
      real_ans2.reverse()
      
      if user_ans == real_ans1 or user_ans == real_ans2:
        test_case_passed = True
        break
      
      WrongAnswerExit(p, test_case_id,
        "Failed to report answer correctly.\n"
        "Expected: {} or {}\n"
        "Read: {}".format(str(real_ans1), str(real_ans2), str(user_ans)))
    else:
      WrongAnswerExit(p, test_case_id, "Each line should start with ? or !")
  if not test_case_passed:
    WrongAnswerExit(p, test_case_id,
      "Failed to report answer in {} turns.".format(MAX_TURNS))

extra_output = p.stdout.readline()
WaitForSubprocess(p)
if extra_output == "":
  print("Congratulations! :)")
else:
  print("Wrong Answer because of extra output:")
  sys.stdout.write(extra_output)
  sys.exit(-1)


