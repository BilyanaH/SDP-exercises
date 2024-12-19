#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
	std::unordered_map<int, int> map;

	for (int i = 0; i < nums.size(); i++)
	{
		int complement = target - nums[i];
		if (map.find(complement) != map.end())
		{
			return { map[complement], i };
		}
		map[nums[i]] = i;
	}
	return{};
}
std::string toLower(std::string input) {
	std::string result = "";
	for (char c : input) {
		result += tolower(c);
	}
	return result;
}
void testTwoSum() {
	std::vector<int> nums1 = { 2, 7, 11, 15 };
	int target1 = 9;
	std::vector<int> result1 = twoSum(nums1, target1);
	assert(result1 == std::vector<int>({ 0, 1 }));

	std::vector<int> nums2 = { 3, 2, 4 };
	int target2 = 6;
	std::vector<int> result2 = twoSum(nums2, target2);
	assert(result2 == std::vector<int>({ 1, 2 }));

	std::vector<int> nums3 = { 3, 3 };
	int target3 = 6;
	std::vector<int> result3 = twoSum(nums3, target3);
	assert(result3 == std::vector<int>({ 0, 1 }));

	std::cout << "All tests passed!" << std::endl;
}
std::string findMostUsedWord(std::string paragraph, std::vector<std::string> banned) {
	paragraph = toLower(paragraph);
	std::unordered_map<std::string, int> map;
	std::string word = "";
	for (char c : paragraph) {
		if (c == ' ' || c == ',' || c == '.' || c == '!' || c == '?') {
			if (word != "") {
				map[word]++;
				word = "";
			}
		}
		else {
			word += c;
		}
	}
	for (int i = 0; i < banned.size(); i++) {
		map.erase(banned[i]);
	}
	std::string mostUsedWord = "";
	int maxCount = 0;
	for (auto pair : map) {
		if (pair.second > maxCount) {
			mostUsedWord = pair.first;
			maxCount = pair.second;
		}
	}
	return mostUsedWord;
}


void testFindMostUsedWord() {
	std::string paragraph1 = "Bob hit a ball, the hit BALL flew far after it was hit.";
	std::vector<std::string> banned1 = { "hit" };
	assert(findMostUsedWord(paragraph1, banned1) == "ball");

	std::string paragraph2 = "a.";
	std::vector<std::string> banned2 = {};
	assert(findMostUsedWord(paragraph2, banned2) == "a");

	std::cout << "All tests passed!" << std::endl;
}
bool compareWords(std::string word1, std::string word2, std::unordered_map<char, int> alphabet) {
	int min = std::min(word1.length(), word2.length());
	for (size_t i = 0; i < min; i++)
	{
		if (alphabet[word1[i]] > alphabet[word2[i]])
			return false;
		if (alphabet[word1[i]] < alphabet[word2[i]])
			return true;
	}
	if (word1.length() > word2.length())
	{
		return false;
	}
	return true;
}
bool AlienDictionary(std::vector<std::string> words, std::string order) {
	std::unordered_map<char, int> alphabet;
	for (int i = 0; i < order.size(); i++)
	{
		alphabet[order[i]] = i;
	}
	for (size_t i = 0; i < words.size() - 1; i++)
	{
		if (!compareWords(words[i], words[i + 1], alphabet))
			return false;
	}
	return true;

}
void testAlienDictionary() {
	std::vector<std::string> words1 = { "hello", "leetcode" };
	std::string order1 = "hlabcdefgijkmnopqrstuvwxyz";
	assert(AlienDictionary(words1, order1) == true);

	std::vector<std::string> words2 = { "word", "world", "row" };
	std::string order2 = "worldabcefghijkmnpqstuvxyz";
	assert(AlienDictionary(words2, order2) == false);

	std::vector<std::string> words3 = { "apple", "app" };
	std::string order3 = "abcdefghijklmnopqrstuvwxyz";
	assert(AlienDictionary(words3, order3) == false);

	std::cout << "All AlienDictionary tests passed!" << std::endl;
}

int main() {
	testTwoSum();
	testFindMostUsedWord();
	testAlienDictionary();
	return 0;
}