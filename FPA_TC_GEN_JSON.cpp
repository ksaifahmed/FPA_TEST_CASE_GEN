#include <bits/stdc++.h>
using namespace std;
#define BIAS 7
//no of test cases
#define CASE_AMOUNT 30

//range of values
#define LO -255
#define HI 255

#define NUM_SYS 2

//decimal places
#define PRECISION 5

string binar(int dig)
{
    string bin = ""; int rem;
    while(dig)
    {
        rem = dig%NUM_SYS; dig/=2;
        bin.append(to_string(rem));
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

tuple<string, string, string> f_to_b(float f)
{
    int sgn = 0;
    if(abs(f)!=f && f!=0.0) sgn = 1;
    string sign = to_string(sgn);
    string bin = binar(abs(int(f)));

    string d_str = to_string(abs(f));
    if(d_str.find(".")<d_str.length()) d_str = d_str.substr(d_str.find("."));
    if(d_str.length()-1>PRECISION) d_str = d_str.substr(0, PRECISION+1);
    float a_dec = stof(d_str); d_str = "";

    while(!(a_dec<(1.0/pow(10, PRECISION))))
    {
        a_dec *= 2;
        d_str.append(to_string(int(a_dec)));
        a_dec = a_dec - float(int(a_dec));
    }
    return make_tuple(bin, d_str, sign);
}


tuple<string, int> pop_zeroes(string bin_l)
{
    int i = 11, expbase = 0;
    while(i--)
    {
        if(bin_l.at(0) == '0')
        {
            bin_l = bin_l.substr(1);
            expbase--;
        }else break;

        if(i==0)
            return make_tuple("0", 0);
    }
    if(bin_l.length()>1) bin_l = bin_l.substr(1);
    expbase--;
    return make_tuple(bin_l, (expbase+BIAS));
}

string standardize(string bin_f, string bin_l, string sgn)
{
    string bin = ""; int exp;
    if(bin_f.length()>1)
    {
        exp = bin_f.length()-1+BIAS;
        bin = bin_f.substr(1) + bin_l;
        if(bin.length()>11) bin = bin.substr(0, 11);
        return sgn+""+binar(exp)+""+bin;
    }

    if(bin_f.empty())
    {
        tie(bin_l, exp) = pop_zeroes(bin_l);
        return sgn+""+binar(exp)+""+bin_l;
    }
    return sgn + "" + binar(BIAS) + "" +bin_l;
}

int main(void){
    int itr = CASE_AMOUNT;
    srand(1);
    float inp1, inp2, ans;
    string bin_f, bin_l, exp;

    freopen("test_cases.json", "w", stdout);
    //cout << "large values:\n======================= "<<endl<<endl;
    cout<<"[\n";
    while(itr--)
    {
        cout<<"{\n";
        inp1 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        inp2 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        ans = inp1 + inp2;

        //std::cout << std::setprecision(PRECISION) << std::fixed;

        tie(bin_f, bin_l, exp) = f_to_b(inp1);
        cout << "\"in1\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;

        tie(bin_f, bin_l, exp) = f_to_b(inp2);
        cout << "\"in2\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;
        tie(bin_f, bin_l, exp) = f_to_b(ans);
        cout << "\"sum\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;

        cout<<"},\n";
    }

    //cout << "small values:\n======================= "<<endl<<endl;
    itr = CASE_AMOUNT;
    while(itr--)
    {
        cout<<"{\n";

        

        inp1 = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        inp2 = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        ans = inp1 + inp2;

        //std::cout << std::setprecision(PRECISION) << std::fixed;

        tie(bin_f, bin_l, exp) = f_to_b(inp1);
        cout << "\"in1\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;

        tie(bin_f, bin_l, exp) = f_to_b(inp2);
        cout << "\"in2\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;
        tie(bin_f, bin_l, exp) = f_to_b(ans);
        cout << "\"sum\"" << " : \"0b" << standardize(bin_f, bin_l, exp) <<"\","<<endl;

        cout<<"},\n";
    }
    cout<<"]\n";
    fclose(stdout);
    return 0;
}
