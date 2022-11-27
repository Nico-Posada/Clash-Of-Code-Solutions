# i was gonna try this one in C but hell no
public def decode
  fix = -> (str) {str.tr($translate[0], $translate[1])}

  slice_n_split = -> (stack) {
    slice = stack.each_slice(2).to_a
    new_stack = []
    2.times do |c|
      for i in 0...slice.size
        new_stack << slice[i][c]||next
      end
    end
    new_stack.join.chars
  }

  stack = []
  result = ''
  shouldDelete = false;

  self.chars.each do |c|
    next if c == ?+

    if shouldDelete
      stack = stack[..~(c.to_i)]
      shouldDelete = false
    elsif c == ?*
      result += stack.pop
    elsif c == ?#
      shouldDelete = true
    elsif c == ?%
      stack = slice_n_split.call(stack)
    else
      stack << c
    end
  end
  fix.call(result)
end

public def newLines!(len)
  put_newline = -> (i) {
    i -= 1 while self[i] != ' '
    self[i] = ?\n
    return i
  }

  idx = -1
  idx = put_newline[idx] while (idx += 76) < len
end

n = gets.to_i
$translate = [''] * 2

n.times do
  left, right = gets.scan(/(\w+) \-> (\w+)/)[0]
  $translate[0] += left
  $translate[1] += right
end

len = gets.to_i
result = gets.decode
result.newLines!(result.size)
puts result
