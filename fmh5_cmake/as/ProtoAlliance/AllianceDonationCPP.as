package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceDonationCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceDonationCPP";
		public var package_root:*;
		public  var message:*;
		public var applyUid:int;
		public var propsid:int;
		public var count:int;
		public var donateCount:int;
		public var fetchCount:int;
		public var status:int;
		public var name:Byte;
		public var donateUid:Vector.<int>;
		public var donateTimes:Vector.<int>;
		public var donateName:Vector.<Byte>;
		public var applyts:int;
		public var level:int;
		public function AllianceDonationCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyUid = undefined;
			propsid = undefined;
			count = undefined;
			donateCount = undefined;
			fetchCount = undefined;
			status = undefined;
			name = undefined;
			donateUid = new Vector.<int>();
			donateTimes = new Vector.<int>();
			donateName = new Vector.<Byte>();
			applyts = undefined;
			level = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyUid = this.applyUid;
			serializeObj.propsid = this.propsid;
			serializeObj.count = this.count;
			serializeObj.donateCount = this.donateCount;
			serializeObj.fetchCount = this.fetchCount;
			serializeObj.status = this.status;
			this.name.pos = 0;
			serializeObj.donateUid = [];
			for(var i:int = 0;i < this.donateUid.length;i++)
			{
				serializeObj.donateUid.push(this.donateUid[i]);
			}
			serializeObj.donateTimes = [];
			for(var i:int = 0;i < this.donateTimes.length;i++)
			{
				serializeObj.donateTimes.push(this.donateTimes[i]);
			}
			serializeObj.donateName = [];
			for(var i:int = 0;i < this.donateName.length;i++)
			{
				serializeObj.donateName.push(this.donateName[i].getUint8Array(0, this.donateName[i].length));
				this.donateName[i].pos = 0;
			}
			serializeObj.applyts = this.applyts;
			serializeObj.level = this.level;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceDonationCPP
		{
			applyUid = undefined;
			propsid = undefined;
			count = undefined;
			donateCount = undefined;
			fetchCount = undefined;
			status = undefined;
			name = undefined;
			donateUid = new Vector.<int>();
			donateTimes = new Vector.<int>();
			donateName = new Vector.<Byte>();
			applyts = undefined;
			level = undefined;
			this.applyUid = msgObj.applyUid;
			this.propsid = msgObj.propsid;
			this.count = msgObj.count;
			this.donateCount = msgObj.donateCount;
			this.fetchCount = msgObj.fetchCount;
			this.status = msgObj.status;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			for(var i:int = 0;i < msgObj.donateUid.length;i++)
			{
				this.donateUid.push(msgObj.donateUid[i]);
			}
			for(var i:int = 0;i < msgObj.donateTimes.length;i++)
			{
				this.donateTimes.push(msgObj.donateTimes[i]);
			}
			for(var i:int = 0;i < msgObj.donateName.length;i++)
			{
				this.donateName[i] = new Byte();
				this.donateName[i].writeArrayBuffer(msgObj.donateName[i]);
				this.donateName[i].pos = 0;
			}
			this.applyts = msgObj.applyts;
			this.level = msgObj.level;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceDonationCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}