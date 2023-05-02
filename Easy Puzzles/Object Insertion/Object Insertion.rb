def check_valid(x, y)
  for i in 0...$obj_h
    for j in 0...$obj_w
      next if @to_insert[i][j] == ?.
      return false if @grid[y+i][x+j] == ?#
    end
  end
  return true
end

$obj_h, $obj_w = gets.split.map &:to_i
@to_insert = $obj_h.times.map{gets.chomp.chars}
grid_h, grid_w = gets.split.map &:to_i
@grid = grid_h.times.map{gets.chomp}

first_find = true
count = 0

for y in 0..grid_h - $obj_h
  for x in 0..grid_w - $obj_w
    valid = check_valid(x, y)

    if valid && first_find
      for i in 0...$obj_h
        for j in 0...$obj_w
          next if @to_insert[i][j] == ?.
          @grid[y+i][x+j] = ?*
        end
      end
      count += 1
      first_find = false
    elsif valid
      count += 1
    end
  end
end

puts count
puts @grid if count == 1
