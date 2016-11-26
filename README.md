# Dispatch
Run sync/async std::function on main/background threads

### Dispatch::async
```
Dispatch::async(Dispatch::Background, []() {
    qDebug() << "Hello from async";
});
qDebug() << "Next line";
```

Output:

```
Next line
Hello from async
```


### Dispatch::sync
```
Dispatch::sync(Dispatch::Background, []() {
    qDebug() << "Hello from sync";
});
qDebug() << "Next line";
```

Output:

```
Hello from sync
Next line
```
