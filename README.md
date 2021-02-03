# How to get working

Get the repo & the submodules
```bash
# if you're cloning the repo for the first time
git clone --recursive -j8 git@github.com:Meisterlama/BwatEngine.git
# if you already have the repo but need the submodules
git submodule update --init --recursive
```

Don't forget to add the isart remote and push as mirror
```bash
git remote add isart $(isart_repo_adress)
git push isart --mirror
```

