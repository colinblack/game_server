package ProtoOperaBattle {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOperaBattle.MemoryRecordCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class EndOperaBattleResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const RECORD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.EndOperaBattleResp.record", "record", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOperaBattle.MemoryRecordCPP; });

		private var record$field:ProtoOperaBattle.MemoryRecordCPP;

		public function clearRecord():void {
			record$field = null;
		}

		public function get hasRecord():Boolean {
			return record$field != null;
		}

		public function set record(value:ProtoOperaBattle.MemoryRecordCPP):void {
			record$field = value;
		}

		public function get record():ProtoOperaBattle.MemoryRecordCPP {
			return record$field;
		}

		/**
		 *  @private
		 */
		public static const GATEID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOperaBattle.EndOperaBattleResp.gateid", "gateid", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var gateid$field:uint;

		private var hasField$0:uint = 0;

		public function clearGateid():void {
			hasField$0 &= 0xfffffffe;
			gateid$field = new uint();
		}

		public function get hasGateid():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set gateid(value:uint):void {
			hasField$0 |= 0x1;
			gateid$field = value;
		}

		public function get gateid():uint {
			return gateid$field;
		}

		/**
		 *  @private
		 */
		public static const DIFFICULTY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOperaBattle.EndOperaBattleResp.difficulty", "difficulty", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var difficulty$field:uint;

		public function clearDifficulty():void {
			hasField$0 &= 0xfffffffd;
			difficulty$field = new uint();
		}

		public function get hasDifficulty():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set difficulty(value:uint):void {
			hasField$0 |= 0x2;
			difficulty$field = value;
		}

		public function get difficulty():uint {
			return difficulty$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasRecord) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, record$field);
			}
			if (hasGateid) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, gateid$field);
			}
			if (hasDifficulty) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, difficulty$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var record$count:uint = 0;
			var gateid$count:uint = 0;
			var difficulty$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (record$count != 0) {
						throw new flash.errors.IOError('Bad data format: EndOperaBattleResp.record cannot be set twice.');
					}
					++record$count;
					this.record = new ProtoOperaBattle.MemoryRecordCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.record);
					break;
				case 2:
					if (gateid$count != 0) {
						throw new flash.errors.IOError('Bad data format: EndOperaBattleResp.gateid cannot be set twice.');
					}
					++gateid$count;
					this.gateid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (difficulty$count != 0) {
						throw new flash.errors.IOError('Bad data format: EndOperaBattleResp.difficulty cannot be set twice.');
					}
					++difficulty$count;
					this.difficulty = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
