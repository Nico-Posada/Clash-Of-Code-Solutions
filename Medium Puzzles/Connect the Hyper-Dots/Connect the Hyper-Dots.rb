def hasCrossed?(start, points)
    zip = start.zip points
    zip.map!{_1*_2}
    return zip.any?{_1<0}
end

def getDist(start, points)
    zip = start.zip points
    sum = 0
    zip.each do |a, b|
        sum += (a-b)**2
    end
    return sum**0.5
end

count, dimensions = gets.split.map &:to_i
points = []
count.times do
  letter, *p = gets.chomp.split
  points << [letter, p.map(&:to_i)]
end

start = [0] * dimensions
while points.size > 0
    min = 1e7
    idx = nil
    for i in 0...points.size
        d = getDist(start, points[i][1])
        if d < min
            min = d
            idx = i
        end
    end
    print ' ' if hasCrossed?(start, points[idx][1])
    start = points[idx][1]
    print points[idx][0]
    points.delete_at(idx)
end

