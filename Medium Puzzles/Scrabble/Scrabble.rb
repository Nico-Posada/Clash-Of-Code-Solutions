public def check(letters)
  copy = letters[0..]
  self.each do |char|
    return -1 if !copy.include?(char)

    copy.delete_at copy.index(char)
  end
  return getValue(self)
end

def getValue(letters)
  keys = {
    ?e => 1, ?a => 1, ?i => 1, ?o => 1, ?n => 1, ?r => 1, ?t => 1, ?l => 1, ?s => 1, ?u => 1,
    ?d => 2, ?g => 2,
    ?b => 3, ?c => 3, ?m => 3, ?p => 3,
    ?f => 4, ?h => 4, ?v => 4, ?w => 4, ?y => 4,
    ?k => 5,
    ?j => 8, ?x => 8,
    ?q => 10, ?z => 10
  }

  sum = 0
  letters.each do |char|
    sum += keys[char]
  end
  return sum
end
_, *words, letters = `cat`.split
letters = letters.chars.sort

results = {}

words.each do |word|
  chars = word.chars.sort
  result = chars.check(letters)
  next if result == -1

  results.store(word, result)
end

results = results.sort_by{[-_2, words.index(_1)]}
puts results[0].first
