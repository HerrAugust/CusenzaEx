/**
 */
package webApplication.content.impl;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import webApplication.content.ContentPackage;
import webApplication.content.MultipleContent;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Multiple Content</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.impl.MultipleContentImpl#isPaginated <em>Paginated</em>}</li>
 *   <li>{@link webApplication.content.impl.MultipleContentImpl#getSize <em>Size</em>}</li>
 * </ul>
 *
 * @generated
 */
public class MultipleContentImpl extends ContentImpl implements MultipleContent {
	/**
	 * The default value of the '{@link #isPaginated() <em>Paginated</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isPaginated()
	 * @generated
	 * @ordered
	 */
	protected static final boolean PAGINATED_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isPaginated() <em>Paginated</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isPaginated()
	 * @generated
	 * @ordered
	 */
	protected boolean paginated = PAGINATED_EDEFAULT;

	/**
	 * The default value of the '{@link #getSize() <em>Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSize()
	 * @generated
	 * @ordered
	 */
	protected static final int SIZE_EDEFAULT = 0;

	/**
	 * The cached value of the '{@link #getSize() <em>Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getSize()
	 * @generated
	 * @ordered
	 */
	protected int size = SIZE_EDEFAULT;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected MultipleContentImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return ContentPackage.Literals.MULTIPLE_CONTENT;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isPaginated() {
		return paginated;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPaginated(boolean newPaginated) {
		boolean oldPaginated = paginated;
		paginated = newPaginated;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, ContentPackage.MULTIPLE_CONTENT__PAGINATED, oldPaginated, paginated));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getSize() {
		return size;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setSize(int newSize) {
		int oldSize = size;
		size = newSize;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, ContentPackage.MULTIPLE_CONTENT__SIZE, oldSize, size));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
			case ContentPackage.MULTIPLE_CONTENT__PAGINATED:
				return isPaginated();
			case ContentPackage.MULTIPLE_CONTENT__SIZE:
				return getSize();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
			case ContentPackage.MULTIPLE_CONTENT__PAGINATED:
				setPaginated((Boolean)newValue);
				return;
			case ContentPackage.MULTIPLE_CONTENT__SIZE:
				setSize((Integer)newValue);
				return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID) {
		switch (featureID) {
			case ContentPackage.MULTIPLE_CONTENT__PAGINATED:
				setPaginated(PAGINATED_EDEFAULT);
				return;
			case ContentPackage.MULTIPLE_CONTENT__SIZE:
				setSize(SIZE_EDEFAULT);
				return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID) {
		switch (featureID) {
			case ContentPackage.MULTIPLE_CONTENT__PAGINATED:
				return paginated != PAGINATED_EDEFAULT;
			case ContentPackage.MULTIPLE_CONTENT__SIZE:
				return size != SIZE_EDEFAULT;
		}
		return super.eIsSet(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		if (eIsProxy()) return super.toString();

		StringBuffer result = new StringBuffer(super.toString());
		result.append(" (paginated: ");
		result.append(paginated);
		result.append(", size: ");
		result.append(size);
		result.append(')');
		return result.toString();
	}

} //MultipleContentImpl
