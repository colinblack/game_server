package ProtoDailyMission {
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
	public dynamic final class DailyMissionCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MISSID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.DailyMissionCPP.missid", "missid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var missid:uint;

		/**
		 *  @private
		 */
		public static const STAR:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.DailyMissionCPP.star", "star", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var star:uint;

		/**
		 *  @private
		 */
		public static const STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.DailyMissionCPP.status", "status", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var status:uint;

		/**
		 *  @private
		 */
		public static const CURRENT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.DailyMissionCPP.current", "current", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var current:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.missid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.star);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.current);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var missid$count:uint = 0;
			var star$count:uint = 0;
			var status$count:uint = 0;
			var current$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (missid$count != 0) {
						throw new flash.errors.IOError('Bad data format: DailyMissionCPP.missid cannot be set twice.');
					}
					++missid$count;
					this.missid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (star$count != 0) {
						throw new flash.errors.IOError('Bad data format: DailyMissionCPP.star cannot be set twice.');
					}
					++star$count;
					this.star = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (status$count != 0) {
						throw new flash.errors.IOError('Bad data format: DailyMissionCPP.status cannot be set twice.');
					}
					++status$count;
					this.status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (current$count != 0) {
						throw new flash.errors.IOError('Bad data format: DailyMissionCPP.current cannot be set twice.');
					}
					++current$count;
					this.current = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
