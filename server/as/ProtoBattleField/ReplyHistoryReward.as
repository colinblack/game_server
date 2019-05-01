package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReplyHistoryReward extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const RESTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyHistoryReward.rests", "rests", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rests:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyHistoryReward.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyHistoryReward.iron", "iron", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var iron$field:uint;

		private var hasField$0:uint = 0;

		public function clearIron():void {
			hasField$0 &= 0xfffffffe;
			iron$field = new uint();
		}

		public function get hasIron():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set iron(value:uint):void {
			hasField$0 |= 0x1;
			iron$field = value;
		}

		public function get iron():uint {
			return iron$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rests);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			if (hasIron) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, iron$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var rests$count:uint = 0;
			var coin$count:uint = 0;
			var iron$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (rests$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyHistoryReward.rests cannot be set twice.');
					}
					++rests$count;
					this.rests = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyHistoryReward.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyHistoryReward.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
