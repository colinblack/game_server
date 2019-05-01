package ProtoGovernAffair {
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
	public dynamic final class AffairItemCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MISSION_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.AffairItemCPP.mission_time", "missionTime", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var missionTime:uint;

		/**
		 *  @private
		 */
		public static const MISSION_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.AffairItemCPP.mission_id", "missionId", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var missionId:uint;

		/**
		 *  @private
		 */
		public static const LOYAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.AffairItemCPP.loyal", "loyal", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loyal:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.missionTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.missionId);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loyal);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mission_time$count:uint = 0;
			var mission_id$count:uint = 0;
			var loyal$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mission_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: AffairItemCPP.missionTime cannot be set twice.');
					}
					++mission_time$count;
					this.missionTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (mission_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: AffairItemCPP.missionId cannot be set twice.');
					}
					++mission_id$count;
					this.missionId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (loyal$count != 0) {
						throw new flash.errors.IOError('Bad data format: AffairItemCPP.loyal cannot be set twice.');
					}
					++loyal$count;
					this.loyal = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
