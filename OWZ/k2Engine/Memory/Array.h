/**
 * 
 * 
 */
#pragma once

/* 
 * ���s���ɃT�C�Y������ł���Œ蒷�z��N���X
 */
template <typename T>
class AllocatedArray
{
private:
    std::unique_ptr<T[]> data_;
    std::size_t size_; //!< �A�j���[�V�������X�g�̔z��̃T�C�Y�����߂邽��

public:
    /* �^�G�C���A�X�istd::vector���Ƃ̌݊����̂��߁j*/
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    /* 
     * �f�t�H���g�R���X�g���N�^ : ��̔z����쐬
     * ���s�O��Create()���ĂԕK�v������
     */ 
    AllocatedArray()
        : data_(nullptr)
        , size_(0)
    {
    }

    // �����T�C�Y�w��̃R���X�g���N�^
    explicit AllocatedArray(std::size_t size) : size_(0) {
        Create(size);
    }

    /* �R�s�[�͋֎~�i�Œ�z��̈Ӑ}���Ȃ��f�B�[�v�R�s�[��h�����߁j*/
    AllocatedArray(const AllocatedArray&) = delete;
    AllocatedArray& operator=(const AllocatedArray&) = delete;

    /* ���L���̈ړ� (�������R�s�[�Ȃ��Ŏ󂯓n����) */
    AllocatedArray(AllocatedArray&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
    }
    /* ���L���̈ړ�(���[�u������Z�q) */
    AllocatedArray& operator=(AllocatedArray&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    /* 
     * ���s���ɔz��̗v�f�����w�肵�ă��������m�ۂ��� 
     * ���łɃ��������m�ۂ���Ă���ꍇ�͍Ċm�� 
     */
    void Create(std::size_t size) {
        if (size > 0) {
            // std::make_unique �ň��S�ɔz����m��
            data_ = std::make_unique<T[]>(size);
            size_ = size;
        }
        else {
            data_.reset();
            size_ = 0;
        }
    }

    // --- ���������std::vector �̂悤�ȃA�N�Z�X�@�\ ---

    /* �C�e���[�^�̎擾 */
    iterator begin() { return data_.get(); }
    iterator end() { return data_.get() + size_; }
    const_iterator begin() const { return data_.get(); }
    const_iterator end() const { return data_.get() + size_; }
    const_iterator cbegin() const { return data_.get(); }
    const_iterator cend() const { return data_.get() + size_; }

    /* �e�� */
    size_type size() const { return size_; }
    bool empty() const { return size_ == 0; }

    /* �v�f�A�N�Z�X */
    reference operator[](size_type pos) { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }

    /* ���E�`�F�b�N�t���A�N�Z�X */
    reference at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("FixedArray::at: index out of bounds");
        return data_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("FixedArray::at: index out of bounds");
        return data_[pos];
    }

    /* ���|�C���^�̎擾 */
    pointer data() { return data_.get(); }
    const_pointer data() const { return data_.get(); }
};
