import urllib.parse
import sys

def generate_html(name):
    html = f'''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Bonjour</title>
    </head>
    <body>
        <h1>Bonjour, {name} !</h1>
        <p>La QUERY_STRING reçue est : {query_string}</p>

        <h2>Variables d'environnement :</h2>
        <ul>
            <li>REQUEST_METHOD: GET</li>
            <li>SCRIPT_FILENAME: {_file_}</li>
            <li>PATH_INFO: /script/test</li>
            <li>QUERY_STRING: {query_string}</li>
        </ul>
    </body>
    </html>
    '''
    return html

if __name__ == "__main__":
    # Simuler une QUERY_STRING
    query_string = "name=alice&age=20"
    params = urllib.parse.parse_qs(query_string)
    name = params.get('name', ['Inconnu'])[0]

    # Générer et afficher la page HTML
    html_output = generate_html(name)
    print(html_output)
