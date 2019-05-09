
echo "请输入要添加的文件名"
read FILE_NAME

echo "请输入更新后添加的说明"
read VAR

git add $FILE_NAME
git commit -m $VAR

git push -u origin master
