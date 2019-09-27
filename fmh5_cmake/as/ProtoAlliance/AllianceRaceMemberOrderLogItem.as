package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceRaceMemberOrderLogItem
	{
		public static const PROTO:String = "ProtoAlliance.AllianceRaceMemberOrderLogItem";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var finish:int;
		public var max:int;
		public var cancel:int;
		public var point:int;
		public var level:int;
		public var fig:Byte;
		public function AllianceRaceMemberOrderLogItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			finish = undefined;
			max = undefined;
			cancel = undefined;
			point = undefined;
			level = undefined;
			fig = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.finish = this.finish;
			serializeObj.max = this.max;
			serializeObj.cancel = this.cancel;
			serializeObj.point = this.point;
			serializeObj.level = this.level;
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig.getUint8Array(0, this.fig.length);
				this.fig.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceMemberOrderLogItem
		{
			uid = undefined;
			finish = undefined;
			max = undefined;
			cancel = undefined;
			point = undefined;
			level = undefined;
			fig = undefined;
			this.uid = msgObj.uid;
			this.finish = msgObj.finish;
			this.max = msgObj.max;
			this.cancel = msgObj.cancel;
			this.point = msgObj.point;
			this.level = msgObj.level;
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = new Byte();
				this.fig.writeArrayBuffer(msgObj.fig);
				this.fig.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceMemberOrderLogItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}