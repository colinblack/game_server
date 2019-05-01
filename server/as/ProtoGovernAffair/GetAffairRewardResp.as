package ProtoGovernAffair {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoGovernAffair.AffairItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetAffairRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.GetAffairRewardResp.coin", "coin", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.GetAffairRewardResp.wood", "wood", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wood:uint;

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.GetAffairRewardResp.food", "food", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var food:uint;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.GetAffairRewardResp.cash", "cash", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const AFFAIR:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.GetAffairRewardResp.affair", "affair", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoGovernAffair.AffairItemCPP; });

		public var affair:ProtoGovernAffair.AffairItemCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.affair);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var cash$count:uint = 0;
			var affair$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAffairRewardResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAffairRewardResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAffairRewardResp.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAffairRewardResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (affair$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAffairRewardResp.affair cannot be set twice.');
					}
					++affair$count;
					this.affair = new ProtoGovernAffair.AffairItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.affair);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
