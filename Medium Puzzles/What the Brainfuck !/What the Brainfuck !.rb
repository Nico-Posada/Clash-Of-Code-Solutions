lineCount,arrSize,inputs=gets.split.map &:to_i

commands = ""
cells = [0] * arrSize

lineCount.times{ commands += gets.gsub(/[^><\+\-\.,\[\]]/,'') }

# syntax error scan
stack = []
commands.chars do |char|
  if char == '['
    stack << char
  elsif char == ']'
    pop = stack.pop
    if pop != '['
      puts "SYNTAX ERROR"
      exit
    end
  end
end

if stack.size > 0
  puts "SYNTAX ERROR"
  exit
end

ptr = 0
read_idx = 0

# interpreter
right_bracket = []
while 1
  command = commands[read_idx]
  case command
  when '>'
    ptr += 1
  when '<'
    ptr -= 1
  when '+'
    cells[ptr] += 1
  when '-'
    cells[ptr] -= 1
  when '.'
    print cells[ptr].chr
  when ','
    cells[ptr] = gets.to_i
  when '['
    right_bracket << read_idx
    if cells[ptr] == 0
      read_idx = commands.select{_1 == ?] && _1 > read_idx}.first
      right_bracket.pop
    end
  when ']'
    get_idx = right_bracket[~0]
    if cells[ptr] != 0
      read_idx = get_idx
    else
      right_bracket.pop
    end
  end
  read_idx += 1

  if ptr == arrSize || ptr == -1
    puts "POINTER OUT OF BOUNDS"
    exit
  elsif cells[ptr] < 0 || cells[ptr] > 255
    puts "INCORRECT VALUE"
    exit
  end

  break if read_idx == commands.size
end
