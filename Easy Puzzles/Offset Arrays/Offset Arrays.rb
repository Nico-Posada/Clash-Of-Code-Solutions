n = gets.to_i
map = {}
n.times do |i|
  assignment = gets.chomp
  scan = assignment.scan(/(.+)\[(-?\d+)\.\.(-?\d+)\] = (.+)$/)[0]
  range = [*scan[1].to_i..scan[2].to_i]
  idx = -1
  scan.last.scan(/-?\d+/){map.store("#{scan[0]}[#{range[idx += 1]}]", $&.to_i)}
end

result = gets.chomp
while 1
    temp = result[0..] # string duplicating in ruby
    result.gsub!(/\w+\[-?\d+\]/){map[$&]}
    break if result == temp
end

puts result
