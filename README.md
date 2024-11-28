# Aferidor de Pressão de Pneu

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

[![Product Name Screen Shot][product-screenshot]](https://github.com/fmassaretto/tire-pressure-monitor)

> A proposta deste trabalho é desenvolver um aferidor de pressão de pneus, que possibilite ao usuário visualizar, em tempo real, a pressão do pneu em uma tela OLED. Além disso, o sistema exibirá uma pressão recomendada, levando em consideração a temperatura ambiente no momento da aferição, permitirá a troca entre as escalas de medida (PSI e BAR) e incluirá um LED auxiliar para iluminação.

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:

- Você instalou a versão mais recente da extensão para Visual Code `ESP-IDF v5.3`.
- Você tem as extensões `C/C++` e `C/C++ Extension Pack`.
- Você leu `https://github.com/eng-software/ProjetandoDispComerciais/tree/main/Apresenta%C3%A7%C3%B5es`, para saber como configurar todo o ambiente.

## 🚀 Instalando Aferidor de Pressão de Pneu

Para instalar o Aferidor de Pressão de Pneu, siga estas etapas:

Linux e macOS:

```
<comando_de_instalação>
```

Windows:

1. Clone o repositório
   ```sh
   git clone https://github.com/fmassaretto/tire-pressure-monitor.git
   ```
2. Mude a url remota para evitar pushes acidentais na base do projeto
   ```sh
   git remote set-url origin github_username/repo_name
   git remote -v # confirm the changes
   ```

## ☕ Usando Aferidor de Pressão de Pneu

Para usar Aferidor de Pressão de Pneu, siga estas etapas:

No Visual Code, para fazer o build do projeto:

```
Clique no icone de uma chave de boca, no canto inferior (ESP-IDF: Build Projet)
```

e para enviar o código para o ESP:
```
Clique no icone de uma chama, no canto inferior (ESP-IDF: Build, Flash and Monitor)
```


## 📫 Contribuindo para Aferidor de Pressão de Pneu

Para contribuir com Aferidor de Pressão de Pneu, siga estas etapas:

1. Bifurque este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie a solicitação de pull.

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).

## 🤝 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="#" title="Foto de perfil de Fábio Massaretto">
        <img src="https://avatars.githubusercontent.com/u/15135415?v=4" width="100px;" alt="Foto de perfil Fabio Massaretto no GitHub"/><br>
        <sub>
          <b>Fábio Massaretto</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

## 😄 Seja um dos contribuidores

Quer fazer parte desse projeto? Clique [AQUI](CONTRIBUTING.md) e leia como contribuir.

## 📝 Licença

Esse projeto está sob licença. Veja o arquivo [LICENÇA](LICENSE.md) para mais detalhes.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/badge/Contributors-1-blue?style=for-the-badge
[contributors-url]: https://github.com/fmassaretto/tire-pressure-monitor/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/fmassaretto/tire-pressure-monitor/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/fmassaretto/tire-pressure-monitor/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/fmassaretto/tire-pressure-monitor/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/fmassaretto/tire-pressure-monitor/blob/main/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/fmassaretto/
[product-screenshot]: pressure_gauge.jpg
