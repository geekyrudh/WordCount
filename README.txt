# WordCount
Keep track of the frequency of each word in a given \n delimited string. String library not used.

//Find the number of occurences of each word in a given text.

1. Identify a word
	1.1 Two letters or more. Minimum length denoted by a constant.
	1.2 Delimited by either a space or a full stop. List of delimiters in an array of strings
	1.3 Starts with a letter
	1.4 Case insensitive

2. Look in the Linked List if the word already exists in it. 
	2.1 Letters are used for determining lexicographical order.
	2.2 For comparing the current word and the next node, if it's not the end of the word,
    	2.2.1 If the two characters are letters and in the same case, compare them directly
    	2.2.2 If the two characters are letters and of different cases, compare them by shifting upper case to lower
    	2.2.3 If they two characters are not letters, let them be
  	2.3 If letters are not available, ASCII values of the characters are used
	2.4 If letters are matched but symbols aren't, ASCII values of the symbols are used
	2.5 If the current word is lexicographically lower than the next list item, it doesn't exist
	2.6 If it is lexicographically equal, it exists
	2.7 if it is lexicographically greater, go to the next node.

3. If it doesn't exist, insert it. Set its count to 1
	3.1 Insert it after the current list node
	3.2 If it's the beginning, follow procedure for insertion at the beginning of list

4. If it exists, increase its count by 1

5. Print list of words and respective counts
