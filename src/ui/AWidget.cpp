#include "AWidget.h"

AWidget::AWidget(sRect size): size_(size)
{
}

bool AWidget::take_dirty_flag()
{
    auto result = dirty_;
    dirty_ = false;
    return result;
}

void AWidget::set_dirty_flag()
{
    dirty_ = true;
}

void AWidget::set_new_size(sRect new_rect)
{
    size_ = new_rect;
}
