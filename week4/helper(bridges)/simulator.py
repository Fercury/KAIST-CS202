"""Python script for testing your solution on your computer
To avoid encoding issues, all instructions are written in English.
You are always free to ask about the testing tool on the Piazza board.

WARNING: This script is only a convenient way to test your solution,
but obviously IT IS NOT SAME WITH THE REAL JUDGING SYSTEM.
The judging system might behave differently.

WARNING: This script has intentionally slow time complexity.
It requires O(|bridges|^2) time to check whether the bridges given in the input don't intersect with each other,
and O(|bridge|) time to answer each sailing request.
"""

from __future__ import print_function
import sys
import subprocess
import argparse

parser = argparse.ArgumentParser("Local testing script for problem 'bridges'.")

parser.add_argument('--input', metavar='INPUTFILENAME', type=argparse.FileType('r'), help='Input file written as the problem statement. If not specified, example input is used.')
parser.add_argument('-l', '--log', help='If specified, show all interaction log', action='store_true')
parser.add_argument('--limit', metavar='LIMIT', type=int, help='Maximum number of sailing requests. Defaults to 100000.', default=100000)
parser.add_argument('command', nargs=argparse.REMAINDER, help='Command to run your C/C++/Java program. You should NOT wrap it with quotation marks.\n')
args = parser.parse_args()

PRINT_INTERACTION_HISTORY = args.log
MAX_SAILING_REQUESTS = args.limit

if args.input is None:
  N = 9
  BRIDGES = [(1, 3), (4, 3), (5, 4), (5, 5), (5, 7), (6, 7), (7, 8), (9, 8)]
else:
  try:
    with args.input as f:
      tokens = f.read().split()
      token_idx = 0
      def next():
        global token_idx
        if token_idx == len(tokens):
          raise ValueError("Number of tokens doesn't match.")
        token_idx += 1
        return int(tokens[token_idx-1])
      n = next()
      if n < 1 or n > 50000:
        raise ValueError("n is out of range [1, 600].")
      num_bridges = next()
      bridges = []
      bridgeset = set()
      for _ in range(num_bridges):
        i = next()
        j = next()
        if i < 1 or i > n:
          raise ValueError("Index of bridge is out of range [1, n]: Line {}, index = {}, n = {}".format(_+1, i, n))
        if j < 1 or j > n:
          raise ValueError("Index of bridge is out of range [1, n]: Line {}, index = {}, n = {}".format(_+1, j, n))
        if (i, j) in bridgeset:
          raise ValueError("Bridge ({}, {}) is duplicated.".format(i, j))
        bridges.append((i, j))
        bridgeset.add((i, j))
      N = n
      BRIDGES = bridges
  except ValueError as e:
    print("Input file format is wrong, please check again.\n{}".format(str(e)))
    sys.exit(-1)
  except Exception as e:
    print("Error while parsing input file {}: {}".format(args.input, str(e)))
    sys.exit(-1)


def bridge_cross(a1, b1, a2, b2):
  if a1 == a2 or b1 == b2:
    return False
  if b1 - a1 == b2 - a2:
    return False
  # now y = (b2-a2)x + a2, y = (b1-a1)x + a1 has an intersection point,
  # check whether it is in [0,1] * [1,n]
  if b1 - a1 < b2 - a2:
    a1, a2, b1, b2 = a2, a1, b2, b1
  return 0 <= -a1 + a2 <= (b1 - a1) - (b2 - a2)

for i in range(len(BRIDGES)):
  for j in range(i+1, len(BRIDGES)):
    a1, b1 = BRIDGES[i]
    a2, b2 = BRIDGES[j]
    if bridge_cross(a1, b1, a2, b2):
      raise ValueError("Bridge ({}, {}) and ({}, {}) intersects".format(a1, b1, a2, b2))


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


def CheckSubprocessExit(p):
  # Exit if your code finishes in the middle of a test case.
  if p.poll() is not None:
    print("Your code exited early.")
    PrintSubprocessResults(p)
    sys.exit(-1)


def WrongAnswerExit(p, error_msg):
  print("Failed: {}".format(error_msg))
  try:
    JudgePrint(p, "-202")
  except IOError:
    print("Failed to print -202 because your code finished already.")
  WaitForSubprocess(p)
  sys.exit(-1)

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

JudgePrint(p, "{}".format(N))

test_case_passed = False
for num_queries in range(MAX_SAILING_REQUESTS+1):
  user_input = None
  try:
    user_input = p.stdout.readline()
    tokens = user_input.split()
    if len(tokens) == 0:
      raise Exception()
  except:
    CheckSubprocessExit(p)
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
    WrongAnswerExit(p, exit_msg)
  
  if PRINT_INTERACTION_HISTORY:
    print("Judge reads:", user_input.rstrip())

  if tokens[0] == "?":
    try:
      i, j = map(int, tokens[1:])
    except:
      WrongAnswerExit(p, 
        "Failed to read the sailing request. Expected '?' and two integers ending with one newline character."
        "Read \"{}\" (quotes added to isolate output of your program) instead".format(user_input))
      
    if (i < 1) or (i > N) or (j < 1) or (j > N):
      WrongAnswerExit(p, "Your input is out of range [1, N = {}].".format(N))
    
    ret = 0
    for x, y in BRIDGES:
      if (x, y) == (i, j):
        ret = -1
        break
      if bridge_cross(x, y, i, j):
        ret += 1

    JudgePrint(p, str(ret))
  elif tokens[0] == "!":
    if len(tokens) != 1:
      WrongAnswerExit(p, "You should print '!' in a separate line.") 
    try:
      line = p.stdout.readline()
      num_bridges = int(line.strip())
      user_answer = []
      for _ in range(num_bridges):
        line = p.stdout.readline()
        tok = line.split()
        if len(tok) != 2:
          raise ValueError("After printing '!', each line should contain two integers.")
        x, y = map(int, line.split())
        if x < 1 or x > N or y < 1 or y > N:
          raise ValueError("After printing '!', each line should contain two integers ranging from 1 to N = {}, but read ({}, {}).".format(N, x, y))
        user_answer.append((x, y))
    except Exception as e:
      CheckSubprocessExit(p)
      WrongAnswerExit(p, e)
    
    if sorted(BRIDGES) == sorted(user_answer):
      test_case_passed = True
      break
    
    WrongAnswerExit(p, "Failed to report all bridges correctly.")
  else:
    WrongAnswerExit(p, "Each line should start with ? or !")

if not test_case_passed:
  WrongAnswerExit(p,
    "Failed to report all bridges in {} sailing requests.".format(MAX_SAILING_REQUESTS))

extra_output = p.stdout.readline()
WaitForSubprocess(p)
if extra_output == "":
  print("Congratulations! All test cases passed :)")
else:
  print("Wrong Answer because of extra output:")
  sys.stdout.write(extra_output)
  sys.exit(-1)

