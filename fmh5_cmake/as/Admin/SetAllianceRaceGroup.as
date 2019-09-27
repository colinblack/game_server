package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class SetAllianceRaceGroup
	{
		public static const PROTO:String = "Admin.SetAllianceRaceGroup";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var group:Vector.<AllianceRaceGroup>;
		public function SetAllianceRaceGroup(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			group = new Vector.<AllianceRaceGroup>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.group = [];
			for(var i:int = 0;i < this.group.length;i++)
			{
				serializeObj.group.push(this.group[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetAllianceRaceGroup
		{
			ts = undefined;
			group = new Vector.<AllianceRaceGroup>();
			this.ts = msgObj.ts;
			for(var i:int = 0;i < msgObj.group.length;i++)
			{
				this.group.push(new AllianceRaceGroup(package_root).unserialize(msgObj.group[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetAllianceRaceGroup
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}