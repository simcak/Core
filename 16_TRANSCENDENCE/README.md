Example plain HTML site using GitLab Pages.

Learn more about GitLab Pages at https://pages.gitlab.io and the official
documentation https://docs.gitlab.com/ce/user/project/pages/.

---

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [GitLab CI](#gitlab-ci)
- [GitLab User or Group Pages](#gitlab-user-or-group-pages)
- [Did you fork this project?](#did-you-fork-this-project)
- [Troubleshooting](#troubleshooting)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## GitLab CI

This project's static Pages are built by [GitLab CI][ci], following the steps
defined in [`.gitlab-ci.yml`](.gitlab-ci.yml):

```
image: busybox

pages:
  stage: deploy
  script:
  - echo 'Nothing to do...'
  artifacts:
    paths:
    - public
    expire_in: 1 day
  rules:
    - if: $CI_COMMIT_REF_NAME == $CI_DEFAULT_BRANCH
```

The above example expects to put all your HTML files in the `public/` directory.

## GitLab User or Group Pages

To use this project as your user/group website, you will need one additional
step: just rename your project to `namespace.gitlab.io`, where `namespace` is
your `username` or `groupname`. This can be done by navigating to your
project's **Settings**.

Read more about [user/group Pages][userpages] and [project Pages][projpages].

## Did you fork this project?

If you forked this project for your own use, please go to your project's
**Settings** and remove the forking relationship, which won't be necessary
unless you want to contribute back to the upstream project.

## Troubleshooting

1. CSS is missing! That means that you have wrongly set up the CSS URL in your
   HTML files. Have a look at the [index.html] for an example.

[ci]: https://about.gitlab.com/gitlab-ci/
[index.html]: https://gitlab.com/pages/plain-html/blob/master/public/index.html
[userpages]: https://docs.gitlab.com/ce/user/project/pages/introduction.html#user-or-group-pages
[projpages]: https://docs.gitlab.com/ce/user/project/pages/introduction.html#project-pages

# Architectural Decisions

For our audiobook marketplace project, we made several key architectural decisions to ensure that our application is scalable, maintainable, and meets the needs of our users. Below are the main decisions we made:

## Backend choice:

We chose **Django** as the backend framework for our audiobook marketplace because it provides a strong balance between *development speed*, *maintainability*, *data modeling*, and *long-term scalability*. We also considered Node.js with Express, but ultimately Django’s features and our team’s familiarity with Python made it the better fit for our project. the only feature where we found Node.js for our project was the API-first architecture, but it is possible with Django as well - so we need to just keep that in mind while using Django REST Framework.

By subject, we needed:

- secure user authentication + profile management,
- a relational database with clear entity relationships,
- audiobook catalog management,
- purchases, reviews, and user libraries,
- a recommendation system based on user behavior,
- extensions such as public API endpoints, mobile clients, and analytics.

## Frontend choice:

In the nutshell - all the frontend is a JavaScript. The choises are only how we want to write it. We can use a framework like React (technically library), Vue, Angular, Svelte, etc. Or we can write it in pure JavaScript. We can say that we can use different language - TypeScript for example, but TypeScript is just a superset of JavaScript...

We decided to use React, because it is the most popular frontend framework (library) and it is good for CV.

## Resources
|    link   |  description  |
|     -     |       -       |
| [pong](https://gitlab.com/sada-sil/ft-transcendence)                                 | resource #1 |
| [pong42](https://ehab42.vercel.app/)                                                 | resource #2 |
| [multiPong](https://github.com/LaOuede/42-ft_transcendence)                          | resource #3 |
| [3d-Tic-Tac-Toe](https://github.com/DGross245/42-ft_transcendence)                   | resource #4 |
| [pong](https://github.com/42-Yerevan-Armenia/ft_transcendence-42?tab=readme-ov-file) | resource #5 with a nice graph |
| [3d-pong](https://www.beihaqi.com/project/ft_transcendence)                          | resource #6 |