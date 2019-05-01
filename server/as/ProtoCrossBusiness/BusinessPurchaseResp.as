package ProtoCrossBusiness {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoCrossBusiness.CrossBusinessCPP;
	import User.RewardBagInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BusinessPurchaseResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const GOODS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoCrossBusiness.BusinessPurchaseResp.goods", "goods", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.RewardBagInfo; });

		public var goods:User.RewardBagInfo;

		/**
		 *  @private
		 */
		public static const CROSSBUSINESS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoCrossBusiness.BusinessPurchaseResp.crossbusiness", "crossbusiness", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoCrossBusiness.CrossBusinessCPP; });

		public var crossbusiness:ProtoCrossBusiness.CrossBusinessCPP;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.BusinessPurchaseResp.cash", "cash", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.goods);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.crossbusiness);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var goods$count:uint = 0;
			var crossbusiness$count:uint = 0;
			var cash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (goods$count != 0) {
						throw new flash.errors.IOError('Bad data format: BusinessPurchaseResp.goods cannot be set twice.');
					}
					++goods$count;
					this.goods = new User.RewardBagInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.goods);
					break;
				case 2:
					if (crossbusiness$count != 0) {
						throw new flash.errors.IOError('Bad data format: BusinessPurchaseResp.crossbusiness cannot be set twice.');
					}
					++crossbusiness$count;
					this.crossbusiness = new ProtoCrossBusiness.CrossBusinessCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.crossbusiness);
					break;
				case 3:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: BusinessPurchaseResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
