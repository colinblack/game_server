package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetNotifyResp
	{
		public static const PROTO:String = "ProtoAlliance.GetNotifyResp";
		public var package_root:*;
		public  var message:*;
		public var notifies:Vector.<AllianceNotifyCPP>;
		public function GetNotifyResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			notifies = new Vector.<AllianceNotifyCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.notifies = [];
			for(var i:int = 0;i < this.notifies.length;i++)
			{
				serializeObj.notifies.push(this.notifies[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNotifyResp
		{
			notifies = new Vector.<AllianceNotifyCPP>();
			for(var i:int = 0;i < msgObj.notifies.length;i++)
			{
				this.notifies.push(new AllianceNotifyCPP(package_root).unserialize(msgObj.notifies[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNotifyResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}