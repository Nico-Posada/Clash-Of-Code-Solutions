w, h = gets.split.map &:to_i
starts, *lines, ends = $<.map &:chomp

starts = starts.split
ends = ends.split
lines = lines.map(&:chars).transpose

for i in 0...starts.size
  y_idx = i * 3
  len = h-2
  len.times do |x|
    up = lines[y_idx-1]
    down = lines[y_idx+1]
    if !up.nil? && up[x] == ?-
      y_idx -= 3
    elsif !down.nil? && down[x] == ?-
      y_idx += 3
    end
  end
  puts [starts[i], ends[y_idx/3]]*''
end

