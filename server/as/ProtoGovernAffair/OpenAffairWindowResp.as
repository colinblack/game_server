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
	public dynamic final class OpenAffairWindowResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const AFFAIR:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.OpenAffairWindowResp.affair", "affair", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoGovernAffair.AffairItemCPP; });

		public var affair:ProtoGovernAffair.AffairItemCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.affair);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var affair$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (affair$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenAffairWindowResp.affair cannot be set twice.');
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
