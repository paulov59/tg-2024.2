#include <bits/stdc++.h>

using namespace std;

void dfs(int vertice, vector<bool> &visitado, vector<vector<int>> grafo, stack<int> &pilha)
{
    visitado[vertice] = 1;

    for (auto i : grafo[vertice])
    {
        if (!visitado[i])
        {
            dfs(i, visitado, grafo, pilha);
        }
    }

    pilha.push(vertice);
}

void dfs_reverso(int vertice, vector<bool> &visitado, vector<vector<int>> grafo_reverso, vector<int> &componentes_fortemente_conexas)
{
    visitado[vertice] = 1;
    componentes_fortemente_conexas.push_back(vertice);

    for (auto i : grafo_reverso[vertice])
    {
        if (!visitado[i])
        {
            dfs_reverso(i, visitado, grafo_reverso, componentes_fortemente_conexas);
        }
    }
}

void kosaraju(vector<vector<int>> grafo, vector<vector<int>> grafo_reverso, vector<vector<int>> &componentes_fortemente_conexas)
{
    vector<bool> visitado(grafo.size(), 0);
    stack<int> pilha;

    for (int i = 1; i < visitado.size(); i++)
    {
        if (!visitado[i])
        {
            dfs(i, visitado, grafo, pilha);
        }
    }

    for (int i = 1; i < grafo_reverso.size(); i++)
    {
        visitado[i] = 0;
    }

    while (!pilha.empty())
    {
        int vertice = pilha.top();
        pilha.pop();

        if (!visitado[vertice])
        {
            vector<int> componente;
            dfs_reverso(vertice, visitado, grafo_reverso, componente);
            componentes_fortemente_conexas.push_back(componente);
        }
    }

    return;
}

int main(int argc, char **argv)
{
    int start_node = 1;
    string input_file = "";
    string output_file = "null";

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            output_file = argv[++i];
        }

        else if (strcmp(argv[i], "-f") == 0)
        {
            input_file = argv[++i];
        }
    }

    if (input_file == "")
    {
        cout << "Sem input especificado. Use o parametro -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin)
    {
        cerr << "Não foi possível abrir o arquivo de input: " << input_file << endl;
        return 1;
    }

    int n, m;

    fin >> n >> m;

    vector<vector<int>> grafo(n + 1);

    vector<vector<int>> grafo_reverso(grafo.size());

    vector<vector<int>> componentes_fortemente_conexas;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        fin >> u >> v;

        grafo[u].push_back(v);

        grafo_reverso[v].push_back(u);
    }

    kosaraju(grafo, grafo_reverso, componentes_fortemente_conexas);

    if (output_file != "null")
    {
        ofstream fout(output_file);

        if (!fout)
        {
            cerr << "Não foi possível abrir o arquivo de input: " << output_file << endl;
            return 1;
        }

        for (const auto &cfc : componentes_fortemente_conexas)
        {
            int contador = 0;

            for (int node : cfc)
            {
                if (contador == cfc.size() - 1)
                {
                    fout << node;
                }

                else
                {
                    fout << node << " ";
                }

                contador++;
            }
            fout << endl;
        }

        fout.close();
    }
    else
    {
        for (const auto &component : componentes_fortemente_conexas)
        {
            for (int node : component)
            {
                cout << node << " ";
            }
            cout << endl;
        }
    }

    return 0;
}