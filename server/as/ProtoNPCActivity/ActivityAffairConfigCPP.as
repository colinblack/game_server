package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.AffairConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ActivityAffairConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const DAY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.ActivityAffairConfigCPP.day", "day", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var day:uint;

		/**
		 *  @private
		 */
		public static const AFFAIRS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.ActivityAffairConfigCPP.affairs", "affairs", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.AffairConfigCPP; });

		[ArrayElementType("ProtoNPCActivity.AffairConfigCPP")]
		public var affairs:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.day);
			for (var affairs$index:uint = 0; affairs$index < this.affairs.length; ++affairs$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.affairs[affairs$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var day$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (day$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActivityAffairConfigCPP.day cannot be set twice.');
					}
					++day$count;
					this.day = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.affairs.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.AffairConfigCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
