package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.NPCActivitySingleConfigCPP;
	import User.ActivityItem;
	import ProtoNPCActivity.SpecialNPCCPP;
	import ProtoNPCActivity.NPCActivityCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenNPCActivityWindowResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ACTIVITYITEM:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenNPCActivityWindowResp.activityitem", "activityitem", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.ActivityItem; });

		private var activityitem$field:User.ActivityItem;

		public function clearActivityitem():void {
			activityitem$field = null;
		}

		public function get hasActivityitem():Boolean {
			return activityitem$field != null;
		}

		public function set activityitem(value:User.ActivityItem):void {
			activityitem$field = value;
		}

		public function get activityitem():User.ActivityItem {
			return activityitem$field;
		}

		/**
		 *  @private
		 */
		public static const NPCINFO:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenNPCActivityWindowResp.npcinfo", "npcinfo", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.SpecialNPCCPP; });

		[ArrayElementType("ProtoNPCActivity.SpecialNPCCPP")]
		public var npcinfo:Array = [];

		/**
		 *  @private
		 */
		public static const ACTIVITYCONFIG:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenNPCActivityWindowResp.activityconfig", "activityconfig", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.NPCActivitySingleConfigCPP; });

		private var activityconfig$field:ProtoNPCActivity.NPCActivitySingleConfigCPP;

		public function clearActivityconfig():void {
			activityconfig$field = null;
		}

		public function get hasActivityconfig():Boolean {
			return activityconfig$field != null;
		}

		public function set activityconfig(value:ProtoNPCActivity.NPCActivitySingleConfigCPP):void {
			activityconfig$field = value;
		}

		public function get activityconfig():ProtoNPCActivity.NPCActivitySingleConfigCPP {
			return activityconfig$field;
		}

		/**
		 *  @private
		 */
		public static const ACTIVITY:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenNPCActivityWindowResp.activity", "activity", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.NPCActivityCPP; });

		private var activity$field:ProtoNPCActivity.NPCActivityCPP;

		public function clearActivity():void {
			activity$field = null;
		}

		public function get hasActivity():Boolean {
			return activity$field != null;
		}

		public function set activity(value:ProtoNPCActivity.NPCActivityCPP):void {
			activity$field = value;
		}

		public function get activity():ProtoNPCActivity.NPCActivityCPP {
			return activity$field;
		}

		/**
		 *  @private
		 */
		public static const MULTIPLE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenNPCActivityWindowResp.multiple", "multiple", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var multiple$field:uint;

		private var hasField$0:uint = 0;

		public function clearMultiple():void {
			hasField$0 &= 0xfffffffe;
			multiple$field = new uint();
		}

		public function get hasMultiple():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set multiple(value:uint):void {
			hasField$0 |= 0x1;
			multiple$field = value;
		}

		public function get multiple():uint {
			return multiple$field;
		}

		/**
		 *  @private
		 */
		public static const DAY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenNPCActivityWindowResp.day", "day", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		private var day$field:uint;

		public function clearDay():void {
			hasField$0 &= 0xfffffffd;
			day$field = new uint();
		}

		public function get hasDay():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set day(value:uint):void {
			hasField$0 |= 0x2;
			day$field = value;
		}

		public function get day():uint {
			return day$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasActivityitem) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, activityitem$field);
			}
			for (var npcinfo$index:uint = 0; npcinfo$index < this.npcinfo.length; ++npcinfo$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.npcinfo[npcinfo$index]);
			}
			if (hasActivityconfig) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, activityconfig$field);
			}
			if (hasActivity) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, activity$field);
			}
			if (hasMultiple) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, multiple$field);
			}
			if (hasDay) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, day$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var activityitem$count:uint = 0;
			var activityconfig$count:uint = 0;
			var activity$count:uint = 0;
			var multiple$count:uint = 0;
			var day$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (activityitem$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenNPCActivityWindowResp.activityitem cannot be set twice.');
					}
					++activityitem$count;
					this.activityitem = new User.ActivityItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activityitem);
					break;
				case 2:
					this.npcinfo.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.SpecialNPCCPP()));
					break;
				case 3:
					if (activityconfig$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenNPCActivityWindowResp.activityconfig cannot be set twice.');
					}
					++activityconfig$count;
					this.activityconfig = new ProtoNPCActivity.NPCActivitySingleConfigCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activityconfig);
					break;
				case 4:
					if (activity$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenNPCActivityWindowResp.activity cannot be set twice.');
					}
					++activity$count;
					this.activity = new ProtoNPCActivity.NPCActivityCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activity);
					break;
				case 5:
					if (multiple$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenNPCActivityWindowResp.multiple cannot be set twice.');
					}
					++multiple$count;
					this.multiple = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (day$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenNPCActivityWindowResp.day cannot be set twice.');
					}
					++day$count;
					this.day = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
