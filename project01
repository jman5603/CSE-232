#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::back_inserter;
using std::find;
using std::replace;
using std::min;
using std::transform;
using std::count;
using std::regex;
using std::smatch;
using std::regex_search;
using std::regex_match;
using std::find_first_of;
using std::ptrdiff_t;
using std::distance;
using std::sregex_iterator;

// converts a string with special characters into a regex pattern
string patternToRegex(string const &pattern)
{
    string patternWork = pattern;

    for (int i = 0; i < patternWork.size(); i++)
    {
        if (patternWork[i] == '%')
        {
            patternWork[i] = '.';
        }

        if (patternWork[i] == '#')
        {
            int j = i;
            int count = 1;

            // counting the number of '#' in a row
            while (patternWork[j+1] == '#')
            {
                j++;
                count++;
            }
            if (count == 1)
            {
                patternWork.replace(i, 1, "[0-9]");
            }

            /*  changes the pattern to the regex equivalent
                "?=(...) makes regex look for overlap patterns  */
            else 
            {
                string replacement = "(?=(";
                for (int i = 0; i < patternWork.find('#'); i++)
                {
                    replacement += patternWork[i];
                }
                for (int i = 0; i < count; i++)
                {
                    replacement += "[0-9]";
                }
        
                j++;

                while ((patternWork[j] != '#') && (j < patternWork.size()))
                {
                    replacement += patternWork[j];
                    j++;
                }
                
                replacement += "))";
                return replacement;
            }
        }
    }

    return patternWork;
}

// finds a regex match, builds the matched string, then returns thhe string
string regexSearch(string const &searchText, string const &regexPattern)
{
    regex pattern(regexPattern);
    smatch match;
    regex_search(searchText, match, pattern);

    string matchString = "";
    for (auto i : match)
    {
        matchString += i;
    }

    return matchString;
}

// counts the number of matches of a regex string using string match
int regexMatch(string const &searchText, string const &regexPattern)
{
    smatch match;
    string search = searchText;
    regex pattern(regexPattern);
    
    // counts the distance (number of objects) between an empty iterator and the regex iterator of the search text
    ptrdiff_t count(distance(sregex_iterator(searchText.begin(), searchText.end(), pattern), sregex_iterator()));
    return count;
}

int numDifferences(string const &text1, string const &text2)
{
    int size1 = text1.length();
    int size2 = text2.length();
    int smaller = min(size1, size2);
    int numberOfDifferences = 0;

    for (int i = 0; i < smaller; i++)
        {
            if (text1[i] != text2[i])
            {
                numberOfDifferences++;
            }
        }

    numberOfDifferences += abs(size1 - size2);
    
    return numberOfDifferences;
}

//returns a lowercase version of the input string
string lowerCase(string const &text)
{
    string lower = "";
    transform(text.begin(), text.end(), back_inserter(lower), tolower);
    return lower;
}

int countPatternMatches(string const &searchText, string const &pattern)
{
    string text = searchText;
    int counter = 0;
    while (text.find(pattern) != -1)
    {
        int spot = text.find(pattern);
        text.replace(spot, pattern.size(), "");
        counter++;
    }

    return counter;
}

// uses smatch (string match) from regex to search for the pattern
int regexFindFirstOf(string const &searchText, string const &regexPattern)
{
    smatch match;
    if (regexPattern.find('?') != -1)
    {
        string newPattern = regexPattern;

        /* changes question marks into "escape escape ?", because c++
        needs to escape the backslash and regex needs to escape "?" */
        newPattern.replace(newPattern.find('?'), 1, "\\?");
        regex pattern(newPattern);

        while (regex_search(searchText, match, pattern))
        {
            return match.position();
        }
    }
    regex pattern(regexPattern);
    while (regex_search(searchText, match, pattern))
    {
        int position = match.position();
        return position;
    }
    return -1;
}

bool ImprovedContains(string const &searchText, string const &pattern, bool const *caseInsensitive)
{
    cout.setf(std::ios::boolalpha);
    if (*caseInsensitive)
    {
        string searchLower = lowerCase(searchText);

        string patternLower = lowerCase(pattern);

        // special characters check
        if (patternLower.find('%') != -1 || patternLower.find('#') != -1)
        {
            string foundPattern = regexSearch(searchLower, patternToRegex(patternLower));

            if (foundPattern == "")
            {
                return false;
            }
            return true;
        }
        else
        {
            if (searchLower.find(patternLower) == -1)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    if (*caseInsensitive == false)
    {
        // checks for special characters
        if (pattern.find('%') != -1 || pattern.find('#') != -1)
        {
            string foundPattern = regexSearch(searchText, patternToRegex(pattern));

            if (foundPattern == "")
            {
                return false;
            }
            return true;
        }
        else
        {
            if (searchText.find(pattern) == -1)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

int ImprovedMatches(string const &searchText, string const &pattern, bool const *caseInsensitive)
{

    cout.setf(std::ios::boolalpha);
    if (*caseInsensitive)
    {
        string searchLower = lowerCase(searchText);
        string patternLower = lowerCase(pattern);
        
        if (patternLower.find('%') != -1 || patternLower.find('#') != -1)
        {
            string regexPattern = patternToRegex(patternLower);
            return regexMatch(searchLower, patternLower);
        }
        return countPatternMatches(searchLower, patternLower);
    }

    if (*caseInsensitive == false)
    {
        if (pattern.find('%') != -1 || pattern.find('#') != -1)
        {
            string regexPattern = patternToRegex(pattern);
            return regexMatch(searchText, regexPattern);
        }
    }
    return countPatternMatches(searchText, pattern);
}

int ImprovedFindFirstOf(string const &searchText, string const &pattern, bool const *caseInsensitive)
{
    
    if (*caseInsensitive)
    {
        string searchLower = lowerCase(searchText);
        string patternLower = lowerCase(pattern);

        if (pattern.find('%') != -1 || pattern.find('#') != -1)
        {
            string regexPattern = patternToRegex(pattern);
            return regexFindFirstOf(searchLower, regexPattern);
        }

        return searchLower.find(patternLower);

    }

    if (pattern.find('%') != -1 || pattern.find('#') != -1)
    {
        string regexPattern = patternToRegex(pattern);
        return regexFindFirstOf(searchText, regexPattern);
    }

    return searchText.find(pattern);
}

void ImprovedReplace(string &searchText, string const &pattern, string const &replacement, bool const *caseInsensitive)
{
    if (*caseInsensitive)
    {
        string searchLower = lowerCase(searchText);
        string patternLower = lowerCase(pattern);

        // if special characters are involved
        if (patternLower.find('%') != -1 || patternLower.find('#') != -1)
        {
            string regexPattern = patternToRegex(patternLower);
            int index = regexFindFirstOf(searchLower, regexPattern);
            if (index != -1){
            searchText.replace(index, pattern.size(), replacement);}
        }
        else
        {
            int index = ImprovedFindFirstOf(searchLower, patternLower, caseInsensitive);
            if (index != -1){
            searchText.replace(index, pattern.size(), replacement);}
        }
    }

    else if (*caseInsensitive == false)
    {
        // if special characters are involved
        if (pattern.find('%') != -1 || pattern.find('#') != -1)
        {
            string regexPattern = patternToRegex(pattern);
            int index = regexFindFirstOf(searchText, regexPattern);
            if (index != -1){
            searchText.replace(index, pattern.size(), replacement);}
        }
        else
        {
            int index = ImprovedFindFirstOf(searchText, pattern, caseInsensitive);
            if (index != -1){
            searchText.replace(index, pattern.size(), replacement);}
        }
    }
}

int ImprovedNumberOfDifferences(string const &text1, string const &text2, bool const &caseInsensitive)
{
    cout.setf(std::ios::boolalpha);
    if (caseInsensitive == false)
    {
        return numDifferences(text1, text2);
    }

    if (caseInsensitive == true)
    {
        string lower1 = "";
        string lower2 = "";
        transform(text1.begin(), text1.end(), back_inserter(lower1), tolower);
        transform(text2.begin(), text2.end(), back_inserter(lower2), tolower);

        return numDifferences(lower1, lower2);
    }
}

int main()
{
    return 0;
}
