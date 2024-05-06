#include <stack>
#include <iostream>

struct Call{
    int n; //parameters
    int a, b; // local variables
    int cur_loc; // location of next statement to be executed
};

int F(int n)
{
    if(n<=1) return 1;
    int a=n*F(n-1)+7*F(n/2);
    int b=F(n-3-a%2);
    return a+b;
}
int G(int n)
{// Non-recursive version of FO

    Call initial_call{};
    initial_call.n = n;
    initial_call.cur_loc = 0;

    std::stack<Call> st;
    st.push(initial_call);

    int last_ret_val = 0; // Return value of last finished call

    while (!st.empty())
    {
        Call &call = st.top();

        if (call.cur_loc == 0)
        {
            if (call.n <= 1)
            {
                // Call finished, save return value and pop stack
                last_ret_val = 1;
                st.pop();
            }
            else
            {
                // Make new child call F(n-1) and push to stack
                Call new_call{};
                new_call.cur_loc = 0;
                new_call.n = call.n - 1;
                st.push(new_call);

                // Update current location inside parent call
                call.cur_loc = 1;
            }
        }
        else if (call.cur_loc == 1)
        {
            // Do required computations
            call.a = call.n * last_ret_val;
            // Make new child call F(n/2) and push to stack
            Call new_call{};
            new_call.cur_loc = 0;
            new_call.n = call.n / 2;
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 2;
        }
        else if (call.cur_loc == 2)
        {
            // Do required computations
            call.a += 7 * last_ret_val;
            // Make new child call F(c) and push to stack
            Call new_call{};
            new_call.cur_loc = 0;
            new_call.n = call.n - 3 - call.a % 2;
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 3;
        }
        else if (call.cur_loc == 3)
        {
            // save value of b
            call.b = last_ret_val;
            // Call finished, save return value and pop stack
            last_ret_val = call.a + call.b ;
            st.pop();
        }

    }
    return last_ret_val;
}

int main()
{
    for(int i = 0; i < 20 ;i++)
    {
        std::cout << G(i) <<" " << F(i)<<std::endl;
    }
}
