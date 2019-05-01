package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import User.RewardBagInfo;
	import ProtoActivity.SellComponentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BuyComponentResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const SELLINFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.BuyComponentResp.sellinfo", "sellinfo", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.SellComponentCPP; });

		public var sellinfo:ProtoActivity.SellComponentCPP;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.BuyComponentResp.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.RewardBagInfo; });

		public var reward:User.RewardBagInfo;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.BuyComponentResp.cash", "cash", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const INDEX:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.BuyComponentResp.index", "index", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var index:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.sellinfo);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.index);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var sellinfo$count:uint = 0;
			var reward$count:uint = 0;
			var cash$count:uint = 0;
			var index$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (sellinfo$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuyComponentResp.sellinfo cannot be set twice.');
					}
					++sellinfo$count;
					this.sellinfo = new ProtoActivity.SellComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.sellinfo);
					break;
				case 2:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuyComponentResp.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new User.RewardBagInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 3:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuyComponentResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (index$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuyComponentResp.index cannot be set twice.');
					}
					++index$count;
					this.index = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
