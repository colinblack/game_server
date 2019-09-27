package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class AllianceRaceGroup
	{
		public static const PROTO:String = "Admin.AllianceRaceGroup";
		public var package_root:*;
		public  var message:*;
		public var item:Vector.<AllianceRaceGroupItem>;
		public function AllianceRaceGroup(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			item = new Vector.<AllianceRaceGroupItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceGroup
		{
			item = new Vector.<AllianceRaceGroupItem>();
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new AllianceRaceGroupItem(package_root).unserialize(msgObj.item[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceGroup
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}