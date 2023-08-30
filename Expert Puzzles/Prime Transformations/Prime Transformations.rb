require 'prime'

x = gets.to_i
c = gets.to_i

hash_a = {}
hash_b = {}

c.times do
  ai, bi = gets.split.map &:to_i
  Prime.prime_division(ai).each do |p,q|
    hash_a[p]=[] if !hash_a[p]
    hash_a[p]<<q
  end

  Prime.prime_division(bi).each do |p,q|
    hash_b[p]=[] if !hash_b[p]
    hash_b[p]<<q
  end
end

hash_f = {}
hash_b = hash_b.transform_values &:sort

hash_a.each do |n, vals|
  vals.sort!
  hash_f[n] = hash_b.find{_2 == vals}.first
end

warn hash_f.to_s
p Prime.prime_division(x).map{|p,q| hash_f[p] ? hash_f[p]**q : p**q}.inject(:*)
