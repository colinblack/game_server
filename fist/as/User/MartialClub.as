package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClub
	{
		public static const PROTO:String = "User.MartialClub";
		public var package_root:*;
		public  var message:*;
		public var club:Vector.<SingleMartialClub>;
		public function MartialClub(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			club = new Vector.<SingleMartialClub>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.club = [];
			for(var i:int = 0;i < this.club.length;i++)
			{
				serializeObj.club.push(this.club[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClub
		{
			club = new Vector.<SingleMartialClub>();
			for(var i:int = 0;i < msgObj.club.length;i++)
			{
				this.club.push(new SingleMartialClub(package_root).unserialize(msgObj.club[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClub
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}