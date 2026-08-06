#!/bin/bash
set -e

# ――― 入参校验 ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
VERSION=$1

if [ -z "$VERSION" ]; then
    echo "❌ 请传入版本号，例如: ./release.sh 0.8.9.6"
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PODSPEC="$SCRIPT_DIR/TDOS_Diagnose.podspec"
REPO="BuglyDevTeam/TDOS-Diagnose-iOS"

echo "🚀 开始发布 TDOS_Diagnose $VERSION"
echo ""

# ――― 检查工具 ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
if ! command -v gh &> /dev/null; then
    echo "❌ 未安装 GitHub CLI，请先执行: brew install gh && gh auth login"
    exit 1
fi

# ――― 更新 podspec 版本号 ―――――――――――――――――――――――――――――――――――――――――――――――――――― #
echo "📝 更新 podspec 版本号为 $VERSION ..."
NEW_VERSION="$VERSION" perl -pe 's/(spec\.version\s*=\s*'"'"')([^'"'"']*)'"'"'/$1$ENV{NEW_VERSION}'"'"'/' "$PODSPEC" > "${PODSPEC}.tmp" && mv "${PODSPEC}.tmp" "$PODSPEC"

# ――― 检查是否有改动需要提交 ―――――――――――――――――――――――――――――――――――――――――――――――――― #
cd "$SCRIPT_DIR"

if [ -z "$(git status -s)" ]; then
    echo "⚠️  没有检测到文件改动，跳过 commit 步骤"
else
    echo "📦 提交改动 ..."
    git add -A
    git commit -m "release: sdk升级到${VERSION}版本"
fi

# ――― 检查 tag 是否已存在 ―――――――――――――――――――――――――――――――――――――――――――――――――――― #
if git rev-parse "$VERSION" >/dev/null 2>&1; then
    echo "❌ tag $VERSION 已存在，请确认版本号"
    exit 1
fi

# ――― 推送代码 ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
echo "⬆️  推送代码到远端..."
git push origin HEAD

# ――― 打tag 并推送 ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
echo "🏷️  创建并推送 tag $VERSION ..."
git tag "$VERSION"
git push origin "$VERSION"

# ――― 创建 GitHub Release ――――――――――――――――――――――――――――――――――――――――――――――――――――― #
echo "📋 创建 GitHub Release ..."

gh release create "$VERSION" \
    --title "$VERSION" \
    --generate-notes \
    --repo "$REPO"

# ――― 发布到 CocoaPods trunk ――――――――――――――――――――――――――――――――――――――――――――――――――― #
echo "🍫 发布到 CocoaPods trunk ..."
pod trunk push "$PODSPEC" \
    --verbose \
    --use-libraries \
    --use-modular-headers \
    --allow-warnings \
    --skip-tests \
    --skip-import-validation

echo ""
echo "✅ 发布完成: $VERSION"
echo "🔗 https://github.com/$REPO/releases/tag/$VERSION"
echo "🔗 https://cocoapods.org/pods/TDOS_Diagnose"
