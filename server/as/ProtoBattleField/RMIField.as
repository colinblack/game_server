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
	public dynamic final class RMIField extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const AID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RMIField.aid", "aid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var aid:uint;

		/**
		 *  @private
		 */
		public static const JOB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RMIField.job", "job", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var job:uint;

		/**
		 *  @private
		 */
		public static const IS_ATUO:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoBattleField.RMIField.is_atuo", "isAtuo", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isAtuo:Boolean;

		/**
		 *  @private
		 */
		public static const FORBID_TALK_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RMIField.forbid_talk_ts", "forbidTalkTs", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var forbidTalkTs:uint;

		/**
		 *  @private
		 */
		public static const FORBID_MOVE_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RMIField.forbid_move_ts", "forbidMoveTs", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var forbidMoveTs:uint;

		/**
		 *  @private
		 */
		public static const SILK:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RMIField.silk", "silk", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var silk:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.aid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.job);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isAtuo);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.forbidTalkTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.forbidMoveTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.silk);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var aid$count:uint = 0;
			var job$count:uint = 0;
			var is_atuo$count:uint = 0;
			var forbid_talk_ts$count:uint = 0;
			var forbid_move_ts$count:uint = 0;
			var silk$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (aid$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.aid cannot be set twice.');
					}
					++aid$count;
					this.aid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (job$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.job cannot be set twice.');
					}
					++job$count;
					this.job = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (is_atuo$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.isAtuo cannot be set twice.');
					}
					++is_atuo$count;
					this.isAtuo = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 4:
					if (forbid_talk_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.forbidTalkTs cannot be set twice.');
					}
					++forbid_talk_ts$count;
					this.forbidTalkTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (forbid_move_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.forbidMoveTs cannot be set twice.');
					}
					++forbid_move_ts$count;
					this.forbidMoveTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (silk$count != 0) {
						throw new flash.errors.IOError('Bad data format: RMIField.silk cannot be set twice.');
					}
					++silk$count;
					this.silk = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
