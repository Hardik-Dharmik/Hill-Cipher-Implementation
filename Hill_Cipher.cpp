#include <iostream>
#include <cmath>
using namespace std;

float enc_mess[3][1], key_enc[3][3];

void convert_mess(string s, int n, int m, float enc1[3][1])
{
    for (int i = 0; i < 3; i++)
    {
        enc1[i][0] = s[i] - 'A';
    }
}

void convert_key(string s, int n, int m, float enc1[3][3])
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        enc1[0][k] = s[i] - 'A';
        k++;
    }
    k = 0;
    for (int i = 3; i < 6; i++)
    {
        enc1[1][k] = s[i] - 'A';
        k++;
    }
    k = 0;
    for (int i = 6; i < 9; i++)
    {
        enc1[2][k] = s[i] - 'A';
        k++;
    }
}

int main()
{
    string s;
    string key;
    key = "GYBNQKURP";
    s = "ACT";
    cout<<"\nMessage before encryption:"<<s<<endl;
    cout<<"\nEncryption Key:"<<key<<endl;
    convert_mess(s, 3, 1, enc_mess);
    convert_key(key, 3, 3, key_enc);

    cout << "\nEncrypted Message Matrix:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
            cout << enc_mess[i][j] << " ";
        cout << endl;
    }

    cout << "\nEncrypted Key Matrix:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << key_enc[i][j] << " ";
        cout << endl;
    }

    int mat[3][1], mat2[3][1];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            mat[i][j] = 0;
            mat2[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                mat[i][j] += key_enc[i][k] * enc_mess[k][j];
                mat2[i][j] = mat[i][j];
            }
            mat[i][j] %= 26;
        }
    }

    string encmes = "";
    for (int j = 0; j < 3; j++)
    {
        encmes.push_back(mat[0][j] + 'A');
    }
    cout << "\nMessage after encryption:" << encmes << endl;

    float det = 0;
    float inv[3][3];
    for (int i = 0; i < 3; i++)
        det += (key_enc[0][i] * (key_enc[1][(i + 1) % 3] * key_enc[2][(i + 2) % 3] - key_enc[1][(i + 2) % 3] * key_enc[2][(i + 1) % 3]));


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            inv[i][j] = ((key_enc[(j + 1) % 3][(i + 1) % 3] * key_enc[(j + 2) % 3][(i + 2) % 3]) - (key_enc[(j + 1) % 3][(i + 2) % 3] * key_enc[(j + 2) % 3][(i + 1) % 3])) / det;
        }
    }

    float mat1[3][1];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            mat1[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                mat1[i][j] += inv[i][k] * mat2[k][j];
            }
        }
    }


    cout<<"\nMessage after decryption:";
    for (int j = 0; j < 3; j++)
    {
        cout << (char)(fmod(mat1[j][0], 26) + 65);
    }
    cout<<endl;
}
