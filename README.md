# QDispatch
Run sync/async std::function on main/background threads

### QDispatch::async
```
QDispatch::async(QDispatch::Background, []() {
    qDebug() << "Hello from async";
});
qDebug() << "Next line";
```

Output:

```
Next line
Hello from async
```


### QDispatch::sync
```
QDispatch::sync(QDispatch::Background, []() {
    qDebug() << "Hello from sync";
});
qDebug() << "Next line";
```

Output:

```
Hello from sync
Next line
```
